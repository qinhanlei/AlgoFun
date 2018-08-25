#!/bin/sh

rm ./*.out

gcc -c common.c *sorts.c
ar -r libsorts.a common.o *sorts.o

g++ test.cpp -lsorts -L. -o test.out -std=c++11

rm ./*.o

./test.out
