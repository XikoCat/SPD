#ifndef READ_THREADED_H
#define READ_THREADED_H

#include <stdio.h>
#include <stdlib.h>

long getFileCharCount(char *f);
int *getIntsArray(char *file, int count);
void *read_ints_threaded(void *targ);

typedef struct read_data
{
    //input
    char *file;
    long start;
    long end;

    //output
    int *out;
    int size;

} read_data;

read_data *set_read_data(char *file, long start, long end);

#endif