#!/usr/bin/env bash
./generator --big | time ./lem-in --answer --format=ants \
1> .run.stdout.tmp.test 2> .run.stderr.tmp.test
cat .run.stdout.tmp.test | wc -l >> .run.stderr.tmp.test
cat .run.stderr.tmp.test | awk '\
{
    if (NR == 1)
    {
    $7="\x1B[35m" $7 "\x1B[0m"
    $8="\x1B[38;5;226m" $8 "\x1B[0m"
    print $0
    }
    if (NR == 3)
    {
    $2="\x1B[35m" $2 "\x1B[0m"
    $1="\x1B[38;5;47m" $1 "\x1B[0m"
    print "Lines got: " $0
    }
}'
cat .run.stderr.tmp.test | sed 's/        / /g'| awk '\
{
    if (NR == 2)
    {
    print "\x1B[34mTime:\x1B[0m " $0
    }
}'
rm -f .run.stdout.tmp.test .run.stderr.tmp.test