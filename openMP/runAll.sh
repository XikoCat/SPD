#!/bin/sh
./compile.sh
time for f in ../tests/*.txt;
do
echo "$f";
./a.out "$f";
done