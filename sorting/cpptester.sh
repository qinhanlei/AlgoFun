#!/bin/sh
rm ./*.out
gcc -c common.c
ar rcs libcommon.a common.o
g++ sorting_tester.cpp -lcommon -L. -o _cpptester.out
./_cpptester.out