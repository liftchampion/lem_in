#!/usr/bin/env bash

for (( i=1; i <= 1000000; i++ ))
do
./generator --big > tmp.test
time ./lem-in < tmp.test
done