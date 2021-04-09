#!/bin/sh
./compile.sh
export OMP_NUM_THREADS=4
./a.out "$@"