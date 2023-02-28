#include "kernels.h"

void initialize(long length, long chunk_size, double data_A[length], double data_B[length])
{
    long n_chunks;
    long actual_size;

    n_chunks = length/chunk_size;
    n_chunks = (n_chunks*chunk_size < length)? n_chunks + 1 : n_chunks;

    for (long i = 0; i < length; i += chunk_size) {

        actual_size = (length - i >= chunk_size)? chunk_size : (length - i);
        #pragma omp task depend(out: data_A[i], data_B[i])
        {
			init_kernel(length, actual_size, i, data_A, data_B);
        }
    }
}


// void dot_product(long N, long CHUNK_SIZE, double A[N], double B[N], double *res)
// {
//     long N_CHUNKS;
//     long actual_size;
// 
//     N_CHUNKS = N/CHUNK_SIZE;
//     N_CHUNKS = (N_CHUNKS*CHUNK_SIZE < N)? N_CHUNKS + 1 : N_CHUNKS;
// 
//     for (long i = 0; i < N; i += CHUNK_SIZE) 
//     {
//         actual_size = (N - i >= CHUNK_SIZE)? CHUNK_SIZE : (N - i);
//         #pragma omp task depend(in: A[i], B[i]) depend(inout:res)
// 	{
//             for (long ii = 0; ii < actual_size; ii++)
//                 *res += A[i + ii] * B [i + ii];
//         }
//     }
// }
