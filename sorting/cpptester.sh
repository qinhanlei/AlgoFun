#!/bin/sh
rm ./*.out

gcc -c common.c *_sorts.c
ar -r libsorts.a common.o *_sorts.o

g++ sorting_tester.cpp -lsorts -L. -o _cpptester.out

./_cpptester.out