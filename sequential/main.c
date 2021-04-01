#include <stdio.h>
#include <stdlib.h>

int getSizeFromName(char *file)
{
    char s[11];
    int i = 0;
    char c;
    while (scanf("%c", &c))
        if (c >= 48 && c <= 57)
                s[i++] = c;
    s[i++] = '\0';
    return atoi(s);
}

void solveMagicSquare(int argc, char *argv[])
{
    if (argc < 2)
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