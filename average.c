#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <sys/time.h>

int size_array = 60;

//----------------/Sequencial-----------------------------------------------------------------------//

double ints_fget(FILE *f)
{
  double result = 0;
  double d = 0;

  char c;
  while (fscanf(f, "%c", &c) != EOF)
  {
    if (c == 'u')
    {
      fseek(f, 6, SEEK_CUR);
      char t1[10];
      int tpos = 0;
      while (fscanf(f, "%c", &c) != EOF)
      {
        if (c == 's')
        {
          t1[tpos++] = '\0';
          break;
        }
        if (c == ',')
          c = '.';
        t1[tpos++] = c;
      }
      sscanf(t1, "%lf", &d);
      result += d;
    }
    if (c == 'y')
    {
      fseek(f, 4, SEEK_CUR);
      char t1[10];
      int tpos = 0;
      while (fscanf(f, "%c", &c) != EOF)
      {
        if (c == 's')
        {
          t1[tpos++] = '\0';
          break;
        }
        if (c == ',')
          c = '.';
        t1[tpos++] = c;
      }
      sscanf(t1, "%lf", &d);
      result += d;
    }
  }

  return result;
}

void test_media(const char *filename)
{

  FILE *f = fopen(filename, "r");
  assert(f != NULL);

  double soma = ints_fget(f);
  double media = soma / 30;
  printf("%f\n", media);
}

//----------------/Sequencial-----------------------------------------------------------------------//

//----------------Main-----------------------------------------------------------------------//

int main(int argc, char *argv[])
{
  char *filename = NULL;
  if (argc >= 2)
    filename = argv[1];

  test_media(filename);

  return (0);
}