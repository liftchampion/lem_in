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
        room_tree = {i: [i[0] if '_____' in i else i[0] + '_____'] for i in list_room + [x + '_____' for x in list_room]}
    if rooms:
        list_room.append(s[i][:s[i].find(' ')])
    elif '-' in s[i]:
        #       print 'append ' + s[i][s[i].find('-') + 1:] + ' in ' + s[i][:s[i].find('-')]
        room_tree[s[i][:s[i].find('-')]].append(s[i][s[i].find('-') + 1:] + '_____')
        room_tree[s[i][s[i].find('-') + 1:]].append(s[i][:s[i].find('-')] + '_____')
        #       print room_tree
        #       print ''

print kolichestvo_muraviev
print room_tree
