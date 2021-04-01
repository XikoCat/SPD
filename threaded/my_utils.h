#ifndef MY_UTILS_H
#define MY_UTILS_H

#include <stdio.h>
#include <stdlib.h>

// Verifications
void verify_alloc(void *p);
void verify_fopen(FILE *fp);

// Create array
int *new_int_array(int size);

#endif