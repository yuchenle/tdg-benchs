#include "kernels.h"
#include "timer.h"
#include <malloc.h>
#include <omp.h>
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
  double makespan[50] = {0};
  struct timespec rsss[50];
  struct timespec rsee[50];
  int nthreads = 0;

  long N_CHUNKS = N / CHUNK_SIZE;
  ;
  N_CHUNKS = (N_CHUNKS * CHUNK_SIZE < N) ? N_CHUNKS + 1 : N_CHUNKS;

  START_TIMER;
  for (int i = 0; i < numIter; ++i) {
    res = 0.0;
    initialize(N, CHUNK_SIZE, A, B);
#pragma omp taskwait

#pragma omp parallel shared(nthreads)
    {
      nthreads = omp_get_num_threads();
      double tmp = 0;
      int tid = omp_get_thread_num();
      clock_gettime(CLOCK_MONOTONIC, &rsss[tid]);
#pragma omp for schedule(static, CHUNK_SIZE)
      for (long i = 0; i < N; i++) {
        tmp += A[i] * B[i];
      }
#pragma omp atomic
      res += tmp;

      clock_gettime(CLOCK_MONOTONIC, &rsee[tid]);
      makespan[tid] += (rsee[tid].tv_sec - rsss[tid].tv_sec) * 1000 +
                       (rsee[tid].tv_nsec - rsss[tid].tv_nsec) / 1000000.;
    }
  }
  END_TIMER;
  double maximum = 0;
  double avg = 0;
  for (int i = 0; i < 50; ++i) {
    if (maximum < makespan[i])
      maximum = makespan[i];
    avg += makespan[i];
  }

  printf(
      "Threads recorded %g ms as the maximum, average = %g ms, nthreads = %d\n",
      maximum, avg / nthreads, nthreads);
  // printf("result = %f, size (K), %lu, chunk (K), %lu, time (ms), %g\n", res,
  // N/1024, CHUNK_SIZE/1024, makespan);
  printf("result = %f, size (K), %lu, chunk (K), %lu, time %g ms\n", res,
         N / 1024, CHUNK_SIZE / 1024, wtime);
  return 0;
}
