// Part of the CG (Conjugate gradient) method
// Complete source in BAR/Apps/CG from https://pm.bsc.es/svn/BAR

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#if defined(_OPENMP)
#include <omp.h>
#endif
#include "timer.h"

#define a 1.0

/*
// obsolete, function is inlined
void saxpy(double *x, double *y)
{
    for (int i = 0; i < N; i+=BS1)
    {
        #pragma omp task
        {
            for(int j = 0; j < BS1; j++)
            {
                y[i+j] += a * x[i+j];
            }
        }
    }
}
*/

int main(int argc, char **argv) {
  if (argc != 4) {
    fprintf(stderr, "Usage: %s <vector size> <block number> <num iters>\n",
            argv[0]);
    exit(-1);
  }

  long int N = atoi(argv[1]);
  int NB = atoi(argv[2]);
  int num_iter = atoi(argv[3]);

  int BS = N / NB;

  if (N % NB != 0) {
    fprintf(stderr, "NB should divide N\n");
    exit(-1);
  }

  if (BS > N) {
    fprintf(stderr,
            "block size cannot be greater than the vector size, N = %ld, NB = "
            "%d, BS = %d\n",
            N, NB, BS);
    exit(-1);
  } else {
    printf("executing axpy for %ld elements, divided into %d blocks of %d "
           "elements for %d iters\n",
           N, NB, BS, num_iter);
  }

  double *x, *y;
  x = (double *)malloc(sizeof(double) * N);
  y = (double *)malloc(sizeof(double) * N);

#pragma omp parallel for
  for (int i = 0; i < N; ++i) {
    x[i] = y[i] = 1;
  }

  // double makespan = 0;

  struct timespec rss[50];
  struct timespec rse[50];
  double makespan[50] = {0};
  int nthreads = 0;
  int tid;
#pragma omp parallel shared(nthreads) private(tid)
  {
    for (int iter = 0; iter < num_iter; iter++) {
      tid = omp_get_thread_num();
      nthreads = omp_get_num_threads();
      clock_gettime(CLOCK_MONOTONIC, &rss[tid]);
#pragma omp for schedule(dynamic, BS) // nowait
      for (int i = 0; i < N; i++) {
        y[i] += a * x[i];
      }
      clock_gettime(CLOCK_MONOTONIC, &rse[tid]);
      makespan[tid] += (rse[tid].tv_sec - rss[tid].tv_sec) * 1000 +
                       (rse[tid].tv_nsec - rss[tid].tv_nsec) / 1000000.;
    }
  }

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

#pragma omp parallel for
  for (int i = 0; i < N; ++i) {
    if (y[i] != x[i] * (num_iter) + 1) {
      printf("Erroneous results\n");
      exit(1);
    }
  }

  return 1;
}
