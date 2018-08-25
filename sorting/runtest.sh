#!/bin/sh

gcc -I../utils -c ../utils/common.c *sorts.c
ar -r libsorts.a common.o *sorts.o

g++ -I../utils test.cpp -lsorts -L. -o test.out -std=c++11
./test.out
