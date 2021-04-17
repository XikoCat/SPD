#!/bin/sh
./compile.sh
for f in ../tests/*.txt;
do
echo "$f"
./benchmark.sh "$f" 2> time.txt;
./media.out time.txt;
done