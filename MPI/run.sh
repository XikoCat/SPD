#!/bin/sh
./compile.sh
mpirun -np 2 ./a.out "$@"