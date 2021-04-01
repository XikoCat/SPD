#include "my_utils.h"
#include <stdlib.h>
#include <stdio.h>

void verify_alloc(void *p)
{
    if (!p)
    {
        fprintf(stderr, "Erro a alocar memoria!");
        exit(3);
    }
}

int *new_int_array(int size)
{
    int *array = malloc(size * sizeof(int));
    verify_alloc(array);
    for (int i = 0; i < size; i++)
        array[i] = 0;
    return array;
}
