#!/bin/sh
./compile.sh
time for f in ../tests/*.txt;
do
echo "$f";
mpirun -np 2 ./a.out "$f";
done