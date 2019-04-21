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

start_end = s[0].split(' ')
start = int(start_end[0])
end = int(start_end[1])
s = s[1:]

G = nx.MultiDiGraph()
for i in range(len(s)):
    link = s[i].split(' ')
    if len(link) >= 3:
        G.add_edge(int(link[0]), int(link[1]), capacity=1, weight=int(link[2]))

path = nx.dijkstra_path(G, start, end)
path_len = nx.dijkstra_path_length(G, start, end)

out = open("path.ref.test", 'w')

out.write("Len: " + str(path_len) + '\n')

for nd in path:
    out.write(str(nd) + '\n')


















