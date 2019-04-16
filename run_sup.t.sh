#!/usr/bin/env bash
#make
for (( i=1; i <= 10000000; i++ ))
do
./generator --big-superposition > tmp.test
time ./lem-in < tmp.test
echo "$i"
sleep 2
done