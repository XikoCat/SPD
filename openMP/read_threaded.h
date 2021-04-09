#ifndef READ_THREADED_H
#define READ_THREADED_H

#include <stdio.h>
#include <stdlib.h>

long getFileCharCount(char *f);

typedef struct read_data
{
    //input
    char *file;
    long start;
    long end;
    int count_estimate;

    //output
    int *out;
    int size;

} read_data;

read_data *set_read_data(char *file, long start, long end, int count_estimate);
void free_read_data(read_data *rd);

int *getIntsArrayThreaded(char *file, int count, int thread_count);
void readIntsThreaded(read_data *rd);

#endif