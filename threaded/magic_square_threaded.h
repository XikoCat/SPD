#ifndef MC_THREADED_H
#define MC_THREADED_H

#include <stdio.h>
#include <stdlib.h>

typedef struct magic_solver
{
    //common data
    int *array;
    int line_sum, diag_1, diag_2;
    int *column_sum;
    int target;

    //thread data
    int i, j;
} magic_solver;

magic_solver *set_magic_solver(int array, int line_sum, int diag_1, int diag_2, int target, int i, int j);

#endif