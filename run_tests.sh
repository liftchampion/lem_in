#!/usr/bin/env bash

TESTS=$(ls tests)
for test in $TESTS
do
printf "\x1B[38;5;47m"$test"\x1B[0m\n"
valgrind --leak-check=full --show-leak-kinds=all ./lem-in --vis < tests/$test
echo ""
done