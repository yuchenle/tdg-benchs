#include "kernels.h"
#include "timer.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
long N;
long CHUNK_SIZE;

void initialize(long length, long chunk_size, double data_A[length],
                double data_B[length]);
void dot_product(long N, long CHUNK_SIZE, double A[N], double B[N],
                 double *res);

int main(int argc, char *argv[]) {
  struct timeval start;
  struct timeval stop;
  unsigned long elapsed;
  volatile double result;
  int numIter;

  if (argc != 4) {
    fprintf(stderr,
            "Usage: %s <vector size in K> <chunk size in K> <number of "
            "iterations>\n",
            argv[0]);
    return 1;
  }

  N = atol(argv[1]) * 1024L;
  CHUNK_SIZE = atol(argv[2]) * 1024L;
  numIter = atoi(argv[3]);

  double *A = (double *)malloc(N * sizeof(double));
  double *B = (double *)malloc(N * sizeof(double));

  if (A == NULL || B == NULL) {
    fprintf(stderr, "Error: Can't allocate %ld Bytes\nExiting.\n",
            N * sizeof(double));
    exit(1);
  }

  if (numIter < 0) {
    fprintf(stderr, "number of iterations must be positive\n");
    exit(1);
  }

  double res = 0;
  double makespan = 0;

  long N_CHUNKS = N / CHUNK_SIZE;
  ;
  N_CHUNKS = (N_CHUNKS * CHUNK_SIZE < N) ? N_CHUNKS + 1 : N_CHUNKS;

#pragma omp parallel
#pragma omp single
  for (int i = 0; i < numIter; ++i) {
    res = 0.0;
    double tmp = 0;
    initialize(N, CHUNK_SIZE, A, B);
#pragma omp taskwait

    START_TIMER;
    long actual_size;

#ifdef TDG
#pragma omp taskgraph tdg_type(dynamic)
#pragma omp single nowait
#endif
    for (long i = 0; i < N; i += CHUNK_SIZE) {
      actual_size = (N - i >= CHUNK_SIZE) ? CHUNK_SIZE : (N - i);
#pragma omp task
      {
        double tmp = 0;
        for (long ii = 0; ii < actual_size; ii++)
          tmp += A[i + ii] * B[i + ii];
#pragma omp atomic
        res += tmp;
      }
    }

#ifndef TDG
#pragma omp taskwait // if no taskgraph, explicit taskwait
#endif

    END_TIMER;

    makespan += TIMER;
  }

  printf("result = %f, size (K), %lu, chunk (K), %lu, time (ms), %g\n", res,
         N / 1024, CHUNK_SIZE / 1024, makespan);
  return 0;
}
