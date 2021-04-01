#include <stdio.h>
#include <stdlib.h>
#include "my_utils.c"

int getSizeFromName(char *file)
{
    int p = 0;
    char s[11];
    int i = 0;
    while (file[p] != '\0')
    {
        if (file[p] >= 48 && file[p] <= 57)
            s[i++] = file[p];
        p++;
    }
    s[i++] = '\0';
    return atoi(s);
}

#define NADA "Não é quadrado magico"
#define IMPERFEITO "É quadrado magico imperfeito"
#define PERFEITO "É quadrado magico perfeito"

//reads and determines as it reads
char *determineSquareType(char *file_path)
{
    int squareSize = getSizeFromName(file_path);

    int line_sum = 0, diag_1 = 0, diag_2 = 0;
    int *column_sum = new_int_array(squareSize);
    int target = -1;

    int n = -1;

    FILE *fp = fopen(file_path, "r");
    verify_fopen(fp);

    for (int i = 0; i < squareSize; i++)
    {
        line_sum = 0;
        for (int j = 0; j < squareSize; j++)
        {
            fscanf(fp, "%d", &n);

            line_sum += n;
            column_sum[j] += n;

            if (i == j)
                diag_1 += n;

            if (i == squareSize - 1 - j)
                diag_2 += n;

            if (i == squareSize - 1)
                if (column_sum[j] != target)
                {
                    free(column_sum);
                    return NADA;
                }
        }
        if (i == 0)
            target = line_sum;
        else if (line_sum != target)
        {
            free(column_sum);
            return NADA;
        }
    }
    fclose(fp);

    free(column_sum);

    if (diag_1 == target && diag_2 == target)
        return PERFEITO;
    return IMPERFEITO;
}

void solveMagicSquare(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Missing test file argument");
        exit(3);
    }

    printf("%s", determineSquareType(argv[1]));
}

int main(int argc, char *argv[])
{
    solveMagicSquare(argc, argv);
}