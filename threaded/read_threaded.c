#include "read_threaded.h"

long getFileCharCount(char *f)
{
    FILE *fp = fopen(f, "r");
    verify_file(fp);
    fseek(fp, 0, SEEK_END);
    long r = ftell(fp);
    fclose(fp);
    return r;
}

int *getIntsArray(char *file, int count)
{
}

void *read_ints_threaded(void *targ)
{
}

read_data *set_read_data(char *file, long start, long end)
{
}