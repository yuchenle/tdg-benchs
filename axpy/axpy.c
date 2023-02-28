// Part of the CG (Conjugate gradient) method
// Complete source in BAR/Apps/CG from https://pm.bsc.es/svn/BAR

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#if defined(_OPENMP)
    #include <omp.h>
#endif
#include "timer.h"

#define a   1.0

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

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <vector size> <block number> <iteration number>\n", argv[0]);
        exit(-1);
    }

    long int N = atoi(argv[1]);
    int NB = atoi(argv [2]);
    int num_iter = atoi(argv[3]);
    
    int BS = N/NB;

    if (N % NB != 0)
    {
      fprintf (stderr, "NB should divide N\n");
      exit(-1);
    }

    if (BS > N)
    {
      fprintf (stderr, "block size cannot be greater than the vector size, N = %ld, NB = %d, BS = %d\n", N, NB, BS);
      exit(-1);
    }else{
      printf ("executing axpy for %ld elements, divided into %d blocks of %d elements for %d iters\n", N, NB, BS, num_iter);
    }

    double *x, *y;
    x = (double*)malloc(sizeof(double) * N);
    y = (double*)malloc(sizeof(double) * N);

    #pragma omp parallel for
    for(int i = 0; i < N; ++i){
        x[i] = y[i] = 1;
    }

    double makespan = 0;

    #pragma omp parallel
    #pragma omp single
    {
      for (int i=0; i<num_iter; i++)
      {
        START_TIMER;
        #ifdef TDG
        #pragma omp taskgraph tdg_type(dynamic) 
        #endif
        {
          for (int i = 0; i < N; i+=BS)
          {
              #pragma omp task
              {
                  for(int j = 0; j < BS; j++)
                  {
                      y[i+j] += a * x[i+j];
                  }
              }
          }
        }
        #ifndef TDG
        // y=a*x, change y again if the first iteration is done, not necessary 
        // for taskgraph because there is an implicit taskwait at the end of it
        #pragma omp taskwait 
        #endif
        END_TIMER;
        makespan += TIMER;
      }

      #pragma omp taskwait // final taskwait, might not be necessary
      printf ("%g ms passed\n", makespan);
    }
    

    for (int i = 0; i < N; ++i){
        if (y[i] != x[i]*(num_iter)+1)
        {
            printf("Erroneous results\n");
            exit(1);
        } 
    }

    return 1;
}
