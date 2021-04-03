#include "read_threaded.h"
#include <pthread.h>
#include <string.h>

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
    long total_char_count = getFileCharCount(file);
    double thread_char_count = (double)total_char_count / thread_count;
    int count_estimate = count / thread_count * 2;

    read_data *read_data_list[thread_count];
    verify_alloc(read_data_list);
    pthread_t *thread_list = malloc(thread_count * sizeof(pthread_t));
    verify_alloc(thread_list);

    int *array = malloc(count * sizeof(int));
    verify_alloc(array);
    int size = 0;

    //divide the read task to multiple read_data structs
    long start = 0;
    double end = thread_char_count;
    for (int i = 0; i < thread_count; i++)
    {
        read_data_list[i] = set_read_data(file, start, (long)end, count_estimate);
        pthread_create(&thread_list[i], NULL, readIntsThreaded, (void *)read_data_list[i]);

        start = (long)end;
        if (i == thread_count - 2)
            end = total_char_count;
        else
            end += thread_char_count;
    }
    for (int i = 0; i < thread_count; i++)
    {
        pthread_join(thread_list[i], NULL);
        memcpy(array + size, read_data_list[i]->out, read_data_list[i]->size * sizeof(int));
        size += read_data_list[i]->size;
        free_read_data(read_data_list[i]);

        /*
        for (int i = 0; i < count; i++)
            printf("%d ", array[i]);
        printf("\n");
        */
    }
    //free(read_data_list);
    free(thread_list);

    return array;
}

void *readIntsThreaded(void *targ)
{
    read_data *rd = (read_data *)targ;

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

    return NULL;
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