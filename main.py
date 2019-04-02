#!/usr/bin/python

import sys

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

print room_tree
print "ant count: " + str(kolichestvo_muraviev)
print "start is: " + start + " routes - " + str(len(room_tree[start]) - 1)
print "end is : " + end + " routes - " + str(len(room_tree[end]) - 1)


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
            res[j].append(get_idx(value))
        j += 1
    return res


fill_links(room_tree)
grph = fill_links(room_tree)
ns = get_idx(start)
ne = get_idx(end)
print "NEW start is: " + str(ns)
print "NEW end is: " + str(ne)
# print grph

inf = 10**10


def bell_ford(graph):
    res = []
    for j in range(len(graph)):
        res.append(inf)
    res[ns] = 0
    was_change = 1
    for j in range(len(graph)):
        if not was_change:
            break
        was_change = 0
        for n in range(len(graph)):
            for d in range(len(graph[n])):
                # use link-weight instead of 1
                if res[graph[n][d]] > res[n] + 1:
                    res[graph[n][d]] = res[n] + 1
                    was_change = 1
    print graph
    return res


def print_res(res):
    for j in range(len(res)):
        print idx_to_name[j] + " -> " + str(res[j])


import time
ts = time.time()
rs = bell_ford(grph)
te = time.time()
print_res(rs)
print "\ntime to 1 B-F search is " + str(te - ts)


















