#!/bin/sh
./compile.sh
export OMP_NUM_THREADS=4
time for f in ../tests/*.txt;
do
echo "$f";
./a.out "$f";
done