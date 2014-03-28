#!/bin/sh
gcc totient_range.c -pg
./a.out 1 10000
gprof a.out gmon.out
