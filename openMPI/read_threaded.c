#include "read_threaded.h"
#include "my_utils.h"
#include <mpi.h>
#include <omp.h>
#include <string.h>

long getFileCharCount(char *f) {
  FILE *fp = fopen(f, "r");
  verify_fopen(fp);
  fseek(fp, 0, SEEK_END);
  long r = ftell(fp);
  fclose(fp);
  return r;
}

int *getIntsArrayThreaded(char *file, int count, int thread_count) {
  long total_char_count = getFileCharCount(file);
  double thread_char_count = (double)total_char_count / thread_count;
  int count_estimate = count / thread_count * 2;

  read_data *read_data_list[thread_count];
  verify_alloc(read_data_list);

  int *array = malloc(count * sizeof(int));
  verify_alloc(array);
  int size = 0;

  for (int tid = 0; tid < thread_count; tid++) {
    // send data to satelite
    long start = (long)(tid * thread_char_count);
    long end = (tid != thread_count - 1) ? (long)((1 + tid) * thread_char_count)
                                         : total_char_count;
    read_data_list[tid] = set_read_data(file, start, end, count_estimate);
    if (tid == 0) {
      send_read_data_input(read_data_list[tid], 1);
    } else
      readIntsThreaded(read_data_list[tid]);
  }

  rcv_read_data_output(read_data_list[0], 1);

  for (int i = 0; i < thread_count; i++) {
    memcpy(array + size, read_data_list[i]->out,
           read_data_list[i]->size * sizeof(int));
    size += read_data_list[i]->size;
    free_read_data(read_data_list[i]);
  }
  return array;
}

void readIntsThreaded(read_data *rd) {
  FILE *fp = fopen(rd->file, "r");
  verify_fopen(fp);

  // find nearest int
  if (rd->start != 0) {
    fseek(fp, rd->start - 1, SEEK_SET);
    char c = '\0';
    while (c != ' ')
      fscanf(fp, "%c", &c);
  } else
    fseek(fp, 0, SEEK_SET);

  // pf pointer is now at the start of the closest int

  int *array = malloc(rd->count_estimate * sizeof(int));
  int i = 0;
  int s = 0;
  while (ftell(fp) + s < rd->end) {
    fscanf(fp, "%d", &array[i++]);
    s = 1;
  }
  fclose(fp);

  rd->out = array;
  rd->size = i;
}

read_data *set_read_data(char *file, long start, long end, int count_estimate) {
  read_data *rd = malloc(sizeof(read_data));
  rd->file = file;
  rd->start = start;
  rd->end = end;
  rd->count_estimate = count_estimate;
  return rd;
}

void free_read_data(read_data *rd) {
  free(rd->out);
  free(rd);
}

void sateliteRead() {
  long start;
  long end;
  int count_estimate;
  int file_name_size;
  char file[50];

  MPI_Recv(&file_name_size, 1, MPI_INT, 0, 50, MPI_COMM_WORLD,
           MPI_STATUS_IGNORE);
  MPI_Recv(file, file_name_size, MPI_CHAR, 0, 50, MPI_COMM_WORLD,
           MPI_STATUS_IGNORE);
  file[file_name_size] = '\0';
  MPI_Recv(&start, 1, MPI_LONG, 0, 50, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  MPI_Recv(&end, 1, MPI_LONG, 0, 50, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  MPI_Recv(&count_estimate, 1, MPI_INT, 0, 50, MPI_COMM_WORLD,
           MPI_STATUS_IGNORE);

  //printf("File: %s\n", file);
  FILE *fp = fopen(file, "r");
  verify_fopen(fp);

  // find nearest int
  if (start != 0) {
    fseek(fp, start - 1, SEEK_SET);
    char c = '\0';
    while (c != ' ')
      fscanf(fp, "%c", &c);
  } else
    fseek(fp, 0, SEEK_SET);

  // pf pointer is now at the start of the closest int

  int *out = malloc(count_estimate * sizeof(int));
  int size = 0;
  int s = 0;
  while (ftell(fp) + s < end) {
    fscanf(fp, "%d", &out[size++]);
    s = 1;
  }
  fclose(fp);

  out = out;
  size = size;

  MPI_Send(&size, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
  MPI_Send(out, size, MPI_INT, 0, 50, MPI_COMM_WORLD);
}

void send_read_data_input(read_data *rd, int dest) {
  int l = strlen(rd->file);
  MPI_Send(&l, 1, MPI_INT, dest, 50, MPI_COMM_WORLD);
  MPI_Send(rd->file, l, MPI_CHAR, dest, 50, MPI_COMM_WORLD);
  MPI_Send(&rd->start, 1, MPI_LONG, dest, 50, MPI_COMM_WORLD);
  MPI_Send(&rd->end, 1, MPI_LONG, dest, 50, MPI_COMM_WORLD);
  MPI_Send(&rd->count_estimate, 1, MPI_INT, dest, 50, MPI_COMM_WORLD);
}

void rcv_read_data_output(read_data *rd, int recp) {
  MPI_Recv(&rd->size, 1, MPI_INT, 1, 50, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  rd->out = malloc(rd->size * sizeof(int));
  MPI_Recv(rd->out, rd->size, MPI_INT, 1, 50, MPI_COMM_WORLD,
           MPI_STATUS_IGNORE);
}
