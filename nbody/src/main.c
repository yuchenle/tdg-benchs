/* nbody.c */

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
  if (argc != 4) {
    fprintf(stderr,
            "usage: %s <input file> <particle number> <iteration number>\n",
            argv[0]);
    exit(-1);
  }

  Particle *particle_array = (Particle *)NULL;
  Particle *particle_array2 = (Particle *)NULL;
  int timestep;
  int i;

  FILE *input_data = fopen(argv[1], "r");
  Particle_input_arguments(input_data);

  number_of_timesteps = atoi(argv[3]);
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

  double makespan = 0;

#pragma omp parallel
#pragma omp single
  {
    for (timestep = 1; timestep <= number_of_timesteps; timestep++) {

      START_TIMER;

#ifdef TDG
#pragma omp taskgraph tdg_type(dynamic)
      {
#endif
        for (int i = 0; i < number_of_particles; i++) {
#pragma omp task
          calculate_force_func(time_interval, number_of_particles,
                               particle_array, &particle_array2[i], i);
        }
#ifdef TDG
      }
#else
#pragma omp taskwait
#endif

      END_TIMER;

      makespan += TIMER;
      //printf("iteration %d took %.20f ms\n", timestep, TIMER);
      Particle *tmp = particle_array;
      particle_array = particle_array2;
      particle_array2 = tmp;

    } // for
    // printf("Particles per second: %g \n",
    // (number_of_particles*number_of_timesteps)/(end-start));
    printf("%g ms passed\n", makespan);
  } // single,parallel

  Particle_array_output_xyz(fileptr, particle_array, number_of_particles);

  particle_array = Particle_array_destruct(particle_array, number_of_particles);

  if (fclose(fileptr) != 0) {
    fprintf(stderr, "ERROR: can't close the output file.\n");
    exit(program_failure_code);
  }

  return program_success_code;
}
