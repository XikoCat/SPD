#!/bin/sh
mpirun -np 2 ./a.out $1
#./openmp $1
#mpirun -np 2 mpi $1
#mpirun -np 2 openmpi $1
for ((c=0; c<30; c++))
do
    time mpirun -np 2 ./a.out $1
    #time ./openmp $1
    #time mpirun -np 2 mpi $1
    #time mpirun -np 2 openmpi $1
done


#./benchmark.sh ./tests/p5001.txt 2> times2/times2_p5001.txt 
#./benchmark.sh ./tests/p3.txt 2> times3/times3_p3.txt
#./benchmark.sh ./tests/p3.txt 2> times4/times4_p3.txt
#./benchmark.sh ./tests/p8.txt 2> times4/times4_p8.txt && ./media_run.sh ./times4/times4_p8.txt