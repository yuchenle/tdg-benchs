#include "kernels.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <mkl.h>

int * elapsed_init;
int * elapsed_dotp;
int chunk_size;
int total_spaces;

#define TIME_START struct timespec t1, t2; clock_gettime(CLOCK_MONOTONIC, &t1);
#define TIME_END clock_gettime(CLOCK_MONOTONIC, &t2);
#define TIME_ELAPSED ((t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_nsec - t1.tv_nsec) / 1000)

void init_kernel(long length, long actual_size, long i, double data_A[length], double data_B[length])
{
	// TIME_START;
	for (long ii = 0; ii < actual_size; ++ii) { 
    	data_A[i + ii] = i + ii + 1;
    	data_B[i + ii] = 1;
	}
	// TIME_END;
	// if(chunk_size) elapsed_init[i/chunk_size] = TIME_ELAPSED;
}

double dot_kernel(long N, long actual_size, long i, double A[N], double B[N])
{
	// TIME_START;
   	double acc = 0;
	for (long ii = 0; ii < actual_size; ii++)
       	acc += A[i + ii]*B[i + ii];
	// TIME_END;
	// if(chunk_size) elapsed_dotp[i/chunk_size] = TIME_ELAPSED;
	return acc;
	// return cblas_ddot(actual_size, &A[i], 1, &B[i], 1);
}

void init_diagnostics(int N, int chunk) {
	return;
	int spaces = N/chunk;
	total_spaces = spaces;
	elapsed_init = calloc(spaces, sizeof(int));
	elapsed_dotp = calloc(spaces, sizeof(int));
	chunk_size = chunk;
}

void print_diagnostics() {
	return;
	int spaces = total_spaces;
	int max_init = 0;
	int total_init = 0;
	int max_dot = 0;
	int total_dot = 0;

	for(int i = 0; i < spaces; ++i) {
		if(elapsed_init[i] > max_init)
			max_init = elapsed_init[i];
		total_init += elapsed_init[i];

		if(elapsed_dotp[i] > max_dot)
			max_dot = elapsed_dotp[i];
		total_dot += elapsed_dotp[i];
	}

	printf("Max Init: %d | Avg: %d\n", max_init, total_init/spaces);
	printf("Max Dotp: %d | Avg: %d\n", max_dot, total_dot/spaces);
		
	free(elapsed_init);
	free(elapsed_dotp);
}
