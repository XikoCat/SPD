#include <stdio.h>

int getSizeFromName(char *file)
{
    
    int p = 0;
    while (file[p] < 48 || file[p] > 57)
        p++;
    int r = -1;
    scanf();
}

void solveMagicSquare(int argc, char *argv[])
{
    if(argc < 2)
    {
        perror("Missing test file argument");
        exit(3);
    }
    printf("%d", getSizeFromName(argv[1]));
}

int main(int argc, char *argv[])
{
    solveMagicSquare(argc, argv);
}