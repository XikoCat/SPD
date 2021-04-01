#include "my_utils.h"

void verify_alloc(void *p)
{
    if (!p)
    {
        perror("Erro a alocar memoria!");
        exit(3);
    }
}

void verify_fopen(FILE *fp)
{
    if (fp == NULL){
        perror("Erro ao abrir ficheiro!");
        exit(4);
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
