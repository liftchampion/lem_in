#!/Users/ggerardy/.brew/bin/python3

import sys
import networkx as nx
from networkx import algorithms
from networkx.algorithms import flow
import graphviz
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

G = nx.DiGraph()
start = "lol"
end = "kek"
for i in range(len(s)):
    if '#' in s[i]:
        if '##start' in s[i]:
            i += 1
            words = s[i].split(' ')
            start = words[0]
            G.add_node(words[0], demand=-kolichestvo_muraviev)
            continue
        elif '##end' in s[i]:
            i += 1
            words = s[i].split(' ')
            end = words[0]
            G.add_node(words[0], demand=kolichestvo_muraviev)
            continue
        else:
            continue
    if '-' not in s[i]:
        words = s[i].split(' ')
        G.add_node(words[0])
    else:
        link = s[i].split('-')
        if link[0] == end:
            G.add_edge(link[1], link[0], capacity=1, weight=1)
        elif link[1] == end:
            G.add_edge(link[0], link[1], capacity=1, weight=1)
        elif link[0] == start:
            G.add_edge(link[0], link[1], capacity=1, weight=1)
        elif link[1] == start:
            G.add_edge(link[1], link[0], capacity=1, weight=1)
        else:
            G.add_edge(link[0], link[1], capacity=1, weight=1)
            G.add_edge(link[1], link[0], capacity=1, weight=1)


def count_links(graph):
    res = 0
    for node in graph:
        res += len(node)
    return res


print(start)
print(end)

# nx.draw(G)
# matplotlib.pyplot.show()


print()
# print(nx.algorithms.flow.maximum_flow(G, ns, ne))
print(nx.algorithms.flow.maximum_flow_value(G, start, end))
max_flow = nx.algorithms.flow.maximum_flow(G, start, end)
print(nx.algorithms.flow.cost_of_flow(G, max_flow[1]))
print()
min_cost_flow = nx.algorithms.flow.min_cost_flow(G, start, end)
print(nx.algorithms.flow.cost_of_flow(G, min_cost_flow))



# print(nx.algorithms.max_flow_min_cost(G, ns, ne))


# import time
# ts = time.time()
# rs = bell_ford(grph)
# te = time.time()
# print_res(rs)



















