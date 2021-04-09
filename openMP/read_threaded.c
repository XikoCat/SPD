#include "read_threaded.h"
#include <string.h>
#include <omp.h>

long getFileCharCount(char *f)
{
    FILE *fp = fopen(f, "r");
    verify_fopen(fp);
    fseek(fp, 0, SEEK_END);
    long r = ftell(fp);
    fclose(fp);
    return r;
}

int *getIntsArrayThreaded(char *file, int count, int thread_count)
{
    int tid;
    long total_char_count = getFileCharCount(file);
    double thread_char_count = (double)total_char_count / thread_count;
    int count_estimate = count / thread_count * 2;

    read_data *read_data_list[thread_count];
    verify_alloc(read_data_list);

    int *array = malloc(count * sizeof(int));
    verify_alloc(array);
    int size = 0;

#pragma omp parallel private(thread_count, tid)
    {
        tid = omp_get_thread_num();
        thread_count = omp_get_num_threads();
        long start = (long)(tid * thread_char_count);
        long end = (tid != thread_count - 1) ? (long)((1 + tid) * thread_char_count) : total_char_count;
        read_data_list[tid] = set_read_data(file, start, end, count_estimate);
        readIntsThreaded(read_data_list[tid]);
    }

    for (int i = 0; i < thread_count; i++)
    {
        memcpy(array + size, read_data_list[i]->out, read_data_list[i]->size * sizeof(int));
        size += read_data_list[i]->size;
        free_read_data(read_data_list[i]);
    }
    return array;
}

void readIntsThreaded(read_data *rd)
{
    //printf("S,E: %ld , %ld\n", rd->start, rd->end);

    FILE *fp = fopen(rd->file, "r");
    verify_fopen(fp);

    //find nearest int
    if (rd->start != 0)
    {
        fseek(fp, rd->start - 1, SEEK_SET);
        char c = '\0';
        while (c != ' ')
            fscanf(fp, "%c", &c);
    }
    else
        fseek(fp, 0, SEEK_SET);

    //pf pointer is now at the start of the closest int

    int *array = malloc(rd->count_estimate * sizeof(int));
    int i = 0;
    int s = 0;
    while (ftell(fp) + s < rd->end)
    {
        fscanf(fp, "%d", &array[i++]);
        s = 1;
    }
    fclose(fp);

    rd->out = array;
    rd->size = i;
}

read_data *set_read_data(char *file, long start, long end, int count_estimate)
{
    read_data *rd = malloc(sizeof(read_data));
    rd->file = file;
    rd->start = start;
    rd->end = end;
    rd->count_estimate = count_estimate;
    return rd;
}

void free_read_data(read_data *rd)
{
    free(rd->out);
    free(rd);
}