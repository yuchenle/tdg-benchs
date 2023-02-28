#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include "omp.h"
#include "timer.h"
#include "cholesky.h"

/* P_SOCRATES default values needed */ 

# define DIM 2048
// 8=120 16=816 24=2600 32=5984 48=19600
int NB;
#define BS (DIM/NB)

static double * const matrix = (double[DIM*DIM]) {0};
static double * const original_matrix = (double[DIM*DIM]) {0};
//static double dummy[NB][NB][BS*BS];
double ***dummy;

void omp_potrf(double * const A, int ts, int ld, double (*AhDep)[NB][NB])
{
	static int INFO;
	static const char L = 'L';
	dpotrf_(&L, &ts, A, &ld, &INFO);
}

void omp_trsm(double *A, double *B, int ts, int ld, double (*AhDep)[NB][NB])
{
	static char LO = 'L', TR = 'T', NU = 'N', RI = 'R';
	static double DONE = 1.0;
	dtrsm_(&RI, &LO, &TR, &NU, &ts, &ts, &DONE, A, &ld, B, &ld );
}

void omp_syrk(double *A, double *B, int ts, int ld, double (*AhDep)[NB][NB])
{
	static char LO = 'L', NT = 'N';
	static double DONE = 1.0, DMONE = -1.0;
	dsyrk_(&LO, &NT, &ts, &ts, &DMONE, A, &ld, &DONE, B, &ld );
}

void omp_gemm(double *A, double *B, double *C, int ts, int ld, double (*AhDep)[NB][NB])
{
	static const char TR = 'T', NT = 'N';
	static double DONE = 1.0, DMONE = -1.0;
	dgemm_(&NT, &TR, &ts, &ts, &ts, &DMONE, A, &ld, B, &ld, &DONE, C, &ld);
}

void cholesky_blocked(const int ts, double* Ah[NB][NB], int num_iter)
{
   double makespan = 0;
   #pragma omp parallel
   #pragma omp single
   {
     double (*AhDep)[NB][NB] = (double (*) [NB][NB])Ah;
     //AhDep is passed as argument of omp_potrf/trsm/gemm/syrk for TDG recording mechanism
     for (int iter = 0; iter < num_iter; iter++)
     {
       START_TIMER;
       #ifdef TDG
       #pragma omp taskgraph tdg_type(dynamic)
       #endif
       {
         for (int k = 0; k < NB; k++) {

            #pragma omp task depend(inout:AhDep[k][k])
            omp_potrf (Ah[k][k], ts, ts, AhDep);

            for (int i = k + 1; i < NB; i++) {
               #pragma omp task depend(in:AhDep[k][k]) depend(inout:AhDep[k][i])
               omp_trsm (Ah[k][k], Ah[k][i], ts, ts, AhDep);
            }

            // Update trailing matrix
            for (int l = k + 1; l < NB; l++) {
               for (int j = k + 1; j < l; j++) {
                 #pragma omp task depend(in:AhDep[k][l]) depend(in:AhDep[k][j]) depend(inout:AhDep[j][l])
                  omp_gemm (Ah[k][l], Ah[k][j], Ah[j][l], ts, ts, AhDep);
               }
               #pragma omp task depend(in:AhDep[k][l]) depend(inout:AhDep[l][l])
               omp_syrk (Ah[k][l], Ah[l][l], ts, ts, AhDep);
            }
         }
       }

       #ifndef TDG
       #pragma omp taskwait
       #endif

       END_TIMER;
       makespan += TIMER;

       // reset the matrix
       convert_to_blocks(ts, NB, DIM, (double(*)[DIM]) original_matrix, Ah);
     }
     printf ("%g ms passed\n", makespan);
   }
}

int main(int argc, char* argv[])
{
   if (argc != 3)
   {
     fprintf (stderr, "Usage: <block number> <num_iterations> \n");
     exit(1);
   }

   NB = atoi(argv[1]);
   if (NB > DIM) 
   {
     fprintf (stderr, "NB = %d, DIM = %d, NB must be smaller than DIM\n", NB, DIM);
     exit(-1);
   }

   int num_iter = atoi(argv[2]);
   if (num_iter < 0) 
   {
     fprintf (stderr, "num_iter must be positive\n");
     exit(1);
   }

   char *result[3] = {"n/a","sucessful","UNSUCCESSFUL"};
   const double eps = BLAS_dfpinfo( blas_eps );

   const int  n = DIM;  // matrix size
   const int ts = BS; 	// tile size

   //#CHECK DYNAMIC_BENCH
   printf ("ts = %d\n", ts);

   int check    = 0; 	// check result?

   // Init matrix
   initialize_matrix(n, ts, matrix);

   // Allocate dummy
   dummy = (double ***)malloc(sizeof(double **) * NB);
   for (int i = 0; i < NB; i++) dummy[i] = (double **)malloc(sizeof(double *) * NB);
   for (int i = 0; i < NB; i++)
     for (int j = 0; j < NB; j++)
       dummy[i][j] = (double *)calloc(BS * BS, sizeof(double));

   // Allocate blocked matrix
   double *Ah[NB][NB];
   for (int i = 0; i < NB; i++) {
      for (int j = 0; j < NB; j++) {
         Ah[i][j] = dummy[i][j];
      }
   }

   for (int i = 0; i < n * n; i++ ) {
      original_matrix[i] = matrix[i];
   }

#ifdef VERBOSE
   printf ("Executing ...\n");
#endif

   convert_to_blocks(ts, NB, n, (double(*)[n]) matrix, Ah);

   cholesky_blocked(ts, (double* (*)[NB]) Ah, num_iter);

   convert_to_linear(ts, NB, n, Ah, (double (*)[n]) matrix);

   if ( check ) {
      const char uplo = 'L';
      if ( check_factorization( n, original_matrix, matrix, n, uplo, eps) ) check++;
   }

   // float time = t2;
   // float gflops = (((1.0 / 3.0) * n * n * n) / ((time) * 1.0e+9));

   // Print results
#ifdef VERBOSE
   printf( "============ CHOLESKY RESULTS ============\n" );
   printf( "  matrix size:          %dx%d\n", n, n);
   printf( "  block size:           %dx%d\n", ts, ts);
#ifndef SEQ
   printf( "  number of threads:    %d\n", omp_get_num_threads());
#endif
   printf( "  time (s):             %f\n", time);
   // printf( "  performance (gflops): %f\n", gflops);
   printf( "==========================================\n" );
#else
   // printf("\n N    BS  #blocks   msecs  Result    performance (gflops)\n");
   // printf(" N=%4d  BS=%4d  #BLOCKS=%6d  %9.3fms Res=%2.6f  gflops=%2.6f \n", n, ts, NB*NB, t2*1e3, matrix[n*n-1], gflops);
#endif
   return 0;
}
