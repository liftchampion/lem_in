#!/Users/ggerardy/.brew/opt/python/bin/python3.7



import sys
import networkx as nx
from networkx import algorithms
from networkx.algorithms import flow
import time
import matplotlib
import heapq
from matplotlib import pyplot
from collections import namedtuple
import cProfile, pstats, io
from pstats import SortKey
import heapq

s = sys.stdin.read().split('\n')

kolichestvo_muraviev = int(s[0])
s = s[1:]

rooms = True

start = None
end = None
list_room = []
room_tree = {}

for i in range(len(s)):
    if '#' in s[i]:
        if '##start' in s[i]:
            i += 1
            start = s[i][:s[i].find(' ')]
        elif '##end' in s[i]:
            i += 1
            end = s[i][:s[i].find(' ')]
        else:
            continue
    if '-' in s[i] and rooms:
        rooms = False
        room_tree = {i: [i[:i.find('_____')] if '_____' in i else i + '_____'] for i in list_room + [x + '_____' for x in list_room]}
    if rooms:
        list_room.append(s[i][:s[i].find(' ')])
    elif '-' in s[i]:
        # print 'append ' + s[i][s[i].find('-') + 1:] + ' in ' + s[i][:s[i].find('-')]
        room_tree[s[i][:s[i].find('-')]].append(s[i][s[i].find('-') + 1:] + '_____')
        room_tree[s[i][s[i].find('-') + 1:]].append(s[i][:s[i].find('-')] + '_____')
        # print room_tree
        # print ''

#print(room_tree)
#print("ant count: " + str(kolichestvo_muraviev))
#print("start is: " + start + " routes - " + str(len(room_tree[start]) - 1))
#print("end is : " + end + " routes - " + str(len(room_tree[end]) - 1))


def map_to_arr(graph):
    res = []
    j = 0
    for key in graph:
        res.append(key)
        j += 1
    return res


idx_to_name = map_to_arr(room_tree)


def get_idx(val):
    j = 0
    for n in idx_to_name:
        if val == n:
            return j
        j += 1


predecessors = []
for i in range(len(room_tree)):
    predecessors.append([])

def print_res(res):
    for j in range(len(res)):
        print(idx_to_name[j] + " -> " + str(res[j]))


def fill_links(graph):
    res = []
    j = 0
    for key in graph:
        res.append([])
        for value in graph[key]:
            idx = get_idx(value)
            res[j].append([idx, 1])
        j += 1
    return res


def fill_predecessors(graph):
    for j in range(len(graph)):
        for nd in graph[j]:
            predecessors[nd[0]].append(j)


def print_predecessors(preds):
    for j in range(len(grph)):
        print(idx_to_name[j], "->")
        for nd in preds[j]:
            print(idx_to_name[nd])


fill_links(room_tree)
grph = fill_links(room_tree)
ns = get_idx(start)
ne = get_idx(end)
#print("NEW start is: " + str(ns))
#print("NEW end is: " + str(ne))
# print(grph)
fill_predecessors(grph)
# print(predecessors)
# print_predecessors(predecessors)

inf = 10**10



def bell_ford(graph):
    res = []
    for j in range(len(graph)):
        res.append(inf)
    res[ns] = 0
    # print(res)
    was_change = 1
    for j in range(len(graph)):
        # print(res)
        if not was_change:
            break
        was_change = 0
        for n in range(len(graph)):
            for d in range(len(graph[n])):
                # use link-weight instead of 1
                if res[graph[n][d][0]] > res[n] + graph[n][d][1]:
                    res[graph[n][d][0]] = res[n] + graph[n][d][1]
                    was_change = 1
    # print(res)
    # print(graph)
    return res


def count_links(graph):
    res = 0
    for node in graph:
        res += len(node)
    return res


links_count = count_links(grph)
#print("Links count: " + str(links_count))
#print("Nodes count: " + str(len(grph)))
#print("Average links from node: " + str((links_count / 2.) / (len(grph) / 2.)))

G = nx.MultiDiGraph()
for i in range(len(grph)):
    for k in grph[i]:
        G.add_edge(i, k[0])

# nx.draw(G)
# matplotlib.pyplot.show()


def sift_down(hp, n, not_visited):
    zs = hp[1]
    down = 2 * n + 1
    while down < zs:
        left = down
        right = down + 1
        if right < zs and hp[0][right][0] < hp[0][left][0]:
            tmp = right
        else:
            tmp = left
        if hp[0][n][0] <= hp[0][tmp][0]:
            break
        not_visited[hp[0][n][1]] = tmp
        not_visited[hp[0][tmp][1]] = n
        hp[0][n], hp[0][tmp] = hp[0][tmp], hp[0][n]
        n = tmp
        down = 2 * n + 1


def eject_min(hp, not_visited):
    mn = hp[0][0]
    not_visited[mn[1]] = -1
    hp[0][0] = hp[0][hp[1] - 1]
    not_visited[hp[0][hp[1] - 1][1]] = 0
    hp[1] -= 1
    sift_down(hp, 0, not_visited)
    return mn[1]


def heap_upd(hp, n, not_visited):
    father = (n - 1) // 2
    while father >= 0 and hp[0][n][0] < hp[0][father][0]:
        not_visited[hp[0][n][1]] = father
        not_visited[hp[0][father][1]] = n
        hp[0][n], hp[0][father] = hp[0][father], hp[0][n]
        n = father
        father = (n - 1) // 2


def my_dijkstra(graph, st, en):
    distances = [10000000000] * len(graph)  # array of final distances to all nodes
    distances[st] = 0  # dst from start to start is 0
    heap = [[[0, st]], len(graph)]  # heap with pairs of actual distance and name. will be used for fast taking closest node \
                                    # [0] - array; [1] - len
    not_visited = [0] * len(graph)  # array with match between node-name and place in heap-array (for fast update heap)
    idx = 1
    for j in range(len(graph)):
        if j != st:
            heap[0].append([distances[j], j])
            not_visited[j] = idx
            idx += 1
    # end of preparation
    while heap[1]:
        curr = eject_min(heap, not_visited)
        # if curr == en:
        #    break
        for child in graph[curr]:
            if not_visited[child[0]] >= 0:
                distances[child[0]] = distances[curr] + child[1]
                heap[0][not_visited[child[0]]][0] = distances[child[0]]
                heap_upd(heap, not_visited[child[0]], not_visited)
    return distances


pr = cProfile.Profile()
pr.enable()

#print("\n")
ts = time.time()
my_dijkstra(grph, ns, ne)
te = time.time()
#print("time to 1 MyDijkstra search is " + str(te - ts))


# pr.disable()
# s = io.StringIO()
# sortby = SortKey.CUMULATIVE
# ps = pstats.Stats(pr, stream=s).sort_stats(sortby)
# ps.print_stats()
# print(s.getvalue())
#
#
# pr = cProfile.Profile()
# pr.enable()
#
# ts = time.time()
# nx.dijkstra_predecessor_and_distance(G, ns)
# te = time.time()
# print("time to 1 Dijkstra search is " + str(te - ts))
#
# pr.disable()
# s = io.StringIO()
# sortby = SortKey.CUMULATIVE
# ps = pstats.Stats(pr, stream=s).sort_stats(sortby)
# ps.print_stats()
# print(s.getvalue())
#
# resd = my_dijkstra(grph, ns, ne)
their_d = nx.dijkstra_predecessor_and_distance(G, ns)

res_ref = [-1] * len(grph)
for key in their_d[1]:
    res_ref[key] = their_d[1][key]

# print(resd)
res_ref.sort()

sssss = '\n'.join([str(i) for i in res_ref])

with open('testsp1.test', 'w') as f:
    f.write(sssss + '\n')
# for t in range(len(grph)):
#     if resd[t] != res_ref[t]:
#         print("AAAAA")
#         print(str(resd[t]), " vs ", str(res_ref[t]), "  -  ", t)
#
# print(resd == res_ref)



# import time
# ts = time.time()
# rs = bell_ford(grph)
# te = time.time()
# print_res(rs)



















