#!/bin/sh
rm ./*.out
gcc -c common.c
ar rcs libcommon.a common.o
gcc sorting_tester.c *_sorts.c -lcommon -L. -o _ctester.out
./_ctester.out