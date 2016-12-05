#!/bin/sh

gcc sorting_tester.c common.c *_sorts.c -o _ctester.out
./_ctester.out