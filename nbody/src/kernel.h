#include "nbody.h"

//#pragma oss task in([size]d_particles) inout([size]output) device(cuda)
//ndrange(1, size, 128)
void calculate_force_func(float time_interval, int number_of_particles,
                          Particle *d_particles, Particle *output,
                          int first_local);
