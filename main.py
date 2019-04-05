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

# print room_tree
print("ant count: " + str(kolichestvo_muraviev))
print("start is: " + start + " routes - " + str(len(room_tree[start]) - 1))
print("end is : " + end + " routes - " + str(len(room_tree[end]) - 1))


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


def fill_links(graph):
    res = []
    j = 0
    for key in graph:
        res.append([])
        for value in graph[key]:
            res[j].append([get_idx(value), 1])
        j += 1
    return res


fill_links(room_tree)
grph = fill_links(room_tree)
ns = get_idx(start)
ne = get_idx(end)
print("NEW start is: " + str(ns))
print("NEW end is: " + str(ne))
print(grph)

inf = 10**10


def bell_ford(graph):
    res = []
    for j in range(len(graph)):
        res.append(inf)
    res[ns] = 0
    print(res)
    was_change = 1
    for j in range(len(graph)):
        print(res)
        if not was_change:
            break
        was_change = 0
        for n in range(len(graph)):
            for d in range(len(graph[n])):
                # use link-weight instead of 1
                if res[graph[n][d]] > res[n] + 1:
                    res[graph[n][d]] = res[n] + 1
                    was_change = 1
    print(res)
    print(graph)
    return res


def count_links(graph):
    res = 0
    for node in graph:
        res += len(node)
    return res


links_count = count_links(grph)
print("Links count: " + str(links_count / 2))
print("Nodes count: " + str(len(grph) / 2))
print("Average links from node: " + str((links_count / 2.) / (len(grph) / 2.)))

G = nx.MultiDiGraph()
for i in range(len(grph)):
    for k in grph[i]:
        G.add_edge(i, k[0], capacity=1)

# nx.draw(G)
# matplotlib.pyplot.show()


def sift_down(hp, n, not_visited):
    zs = hp[1]
    down = 2 * n + 1
    while down < zs:
        left = down
        right = down + 1
        tmp = left
        if right < zs and hp[0][right][0] < hp[0][left][0]:
            tmp = right
        if hp[0][n][0] <= hp[0][tmp][0]:
            break
        not_visited[hp[0][n][1]] = tmp
        not_visited[hp[0][tmp][1]] = n
        tmp_swap = hp[0][n]
        hp[0][n] = hp[0][tmp]
        hp[0][tmp] = tmp_swap
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


def heap_upd(hp, n, new, not_visited):
    hp[0][n][0] = new
    father = (n - 1) // 2
    while hp[0][n][0] < hp[0][father][0]:
        not_visited[hp[0][n][1]] = father
        not_visited[hp[0][father][1]] = n
        tmp_swap = hp[0][n]
        hp[0][n] = hp[0][father]
        hp[0][father] = tmp_swap
        n = father
        father = (n - 1) // 2


def my_dijkstra(graph, st, en):
    distances = []  # array of final distances to all nodes
    for j in range(len(graph)):
        distances.append(10000000000)  # fill by inf
    distances[st] = 0  # dst from start to start is 0
    heap = [[[0, st]], len(graph)]  # heap with pairs of actual distance and name. will be used for fast taking closest node
                                    # [0] - array; [1] - len
    not_visited = [-1] * len(graph)  # array with match of node-name and place in heap-array (for fast update heap)
    not_visited[ns] = 0
    t = 1
    for j in range(len(graph)):
        if j != st:
            heap[0].append([distances[j], j])
            not_visited[j] = t
            t += 1
    # print(heap)
    # print(not_visited)
    # eject_min(heap, not_visited)
    # print(heap)
    # print(not_visited)
    # end of preparation
    while heap[1]:
        curr = eject_min(heap, not_visited)
        for child in graph[curr]:
            distances[child[0]] += 0
            distances[curr] += 0
            if not_visited[child[0]] > 0:
                distances[child[0]] = distances[curr] + child[1]
                heap_upd(heap, not_visited[child[0]], distances[child[0]], not_visited)

    print(distances)


    return "END"


print('\n')

ts = time.time()
print(my_dijkstra(grph, ns, ne))
te = time.time()
print("time to 1 MyDijkstra search is " + str(te - ts))
print('\n')

ts = time.time()
print(nx.multi_source_dijkstra(G, {ns}, ne))
te = time.time()
print("time to 1 multi source Dijkstra search is " + str(te - ts))
print('\n')

ts = time.time()
print(nx.single_source_dijkstra(G, ns, ne))
te = time.time()
print("time to 1 single source Dijkstra search is " + str(te - ts))
print('\n')

ts = time.time()
print(nx.dijkstra_path(G, ns, ne))
te = time.time()
print("time to 1 Dijkstra search is " + str(te - ts))
print('\n')

ts = time.time()
print(nx.bidirectional_dijkstra(G, ns, ne))
te = time.time()
print("time to 1 Bi-Dir_Dijkstra search is " + str(te - ts))
print('\n')

ts = time.time()
print(nx.bellman_ford_path(G, ns, ne))
te = time.time()
print("time to 1 B-F search is " + str(te - ts))
print('\n')


def print_res(res):
    for j in range(len(res)):
        print(idx_to_name[j] + " -> " + str(res[j]))


# import time
# ts = time.time()
# rs = bell_ford(grph)
# te = time.time()
# print_res(rs)



















