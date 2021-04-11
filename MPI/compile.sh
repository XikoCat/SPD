#!/bin/sh
rm a.out
echo --- compiling ---
mpicc -Wall -std=c99 -lm -g -fopenmp main.c
echo --- finished ----