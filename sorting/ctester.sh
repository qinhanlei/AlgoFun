#!/bin/sh
rm ./*.out

gcc -c common.c *_sorts.c
ar -r libsorts.a common.o *_sorts.o

gcc sorting_tester.c -lsorts -L. -o _ctester.out

./_ctester.out