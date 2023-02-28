/* nbody.c */
#include <omp.h>
#include "nbody.h"
#include "timer.h"

extern void calculate_force_func(float, int, Particle *, Particle *, int);

double wall_time() {
  struct timespec ts;
  double res;

  clock_gettime(CLOCK_MONOTONIC, &ts);

  res = (double)(ts.tv_sec) + (double)ts.tv_nsec * 1.0e-9;

  return res;
}

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr,
            "usage: %s <input file> <particle number>\n",
            argv[0]);
    exit(-1);
  }

  Particle *particle_array = (Particle *)NULL;
  Particle *particle_array2 = (Particle *)NULL;
  int timestep;
  int i;

  FILE *input_data = fopen(argv[1], "r");
  Particle_input_arguments(input_data);

  number_of_timesteps = 11;

  printf("executing the program %d iterations \n", number_of_timesteps);

  particle_array = Particle_array_construct(number_of_particles);
  particle_array2 = Particle_array_construct(number_of_particles);

  Particle_array_initialize(particle_array, number_of_particles);

  FILE *fileptr = fopen("nbody_out.xyz", "w");
  Particle_array_output_xyz(fileptr, particle_array, number_of_particles);

  if (number_of_particles <= 1) {
    printf("Returning\n");
    return 0;
  }

  Particle_array_initialize(particle_array, number_of_particles);

  struct timespec rsss[50];
  struct timespec rsee[50];
  double makespan[50] = {0};
  int nthreads = 0;

#pragma omp parallel shared(nthreads) private(timestep)
{
  for (int outer_iter = 0; outer_iter < 2; ++outer_iter) {
    nthreads = omp_get_num_threads();
    int tid = omp_get_thread_num();
    clock_gettime(CLOCK_MONOTONIC, &rsss[tid]);
    
    for (timestep = 1; timestep <= number_of_timesteps; timestep++) {
      #pragma omp for schedule(dynamic)
      for (int i = 0; i < number_of_particles; i++) {
        calculate_force_func(time_interval, number_of_particles,
                              particle_array, &particle_array2[i], i);
      }
    } // number iteration
    
    if(outer_iter==1) {
      clock_gettime(CLOCK_MONOTONIC, &rsee[tid]);
      makespan[tid] += (rsee[tid].tv_sec - rsss[tid].tv_sec)*1000 + (rsee[tid].tv_nsec - rsss[tid].tv_nsec) / 1000000.;
    }

    #pragma omp single
    {
      Particle *tmp = particle_array;
      particle_array = particle_array2;
      particle_array2 = tmp;
    } // single
  } // outer iteration
}
  // printf("Particles per second: %g \n",
  // (number_of_particles*number_of_timesteps)/(end-start));
  double maximum = 0;
  double avg = 0;
  for (int i = 0; i < 50; ++i) {
    if (maximum < makespan[i])
      maximum = makespan[i];
    avg+= makespan[i];
  }

  printf("Threads recorded %g ms as the maximum, average = %g ms, nthreads = %d\n", maximum, avg/nthreads,
         nthreads);

  Particle_array_output_xyz(fileptr, particle_array, number_of_particles);

  particle_array = Particle_array_destruct(particle_array, number_of_particles);

  if (fclose(fileptr) != 0) {
    fprintf(stderr, "ERROR: can't close the output file.\n");
    exit(program_failure_code);
  }

  return program_success_code;
}
