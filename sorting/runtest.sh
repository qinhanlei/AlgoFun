#!/bin/sh

rm ./*.out

gcc -c common.c *sorts.c
ar -r libsorts.a common.o *sorts.o

g++ test.cpp -lsorts -L. -o _test.out

rm ./*.o

./_test.out
