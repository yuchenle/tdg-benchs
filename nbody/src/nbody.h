#ifndef nbody_h
#define nbody_h

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define default_domain_size_x 1.0e+18 /* m  */
#define default_domain_size_y 1.0e+18 /* m  */
#define default_domain_size_z 1.0e+18 /* m  */
#define default_mass_maximum 1.0e+18  /* kg */
#define default_time_interval 1.0e+18 /* s  */
#define default_number_of_particles 1000
#define default_number_of_timesteps 100
#define default_timesteps_between_outputs default_number_of_timesteps
#define default_random_seed 12345
#define default_base_filename "nbody"

#define program_failure_code -1
#define program_success_code 0

static float mass_maximum;

#define DEFAULT_STRING_LENGTH 1023

extern const int default_string_length;
extern const int server;
extern char base_filename[DEFAULT_STRING_LENGTH + 1];
extern float domain_size_x;
extern float domain_size_y;
extern float domain_size_z;
extern float time_interval;
extern int number_of_particles;
extern int number_of_timesteps;
extern int timesteps_between_outputs;
extern unsigned int random_seed;

#define gravitational_constant 6.6726e-11 /* N(m/kg)2 */

typedef struct {
  float position_x; /* m   */
  float position_y; /* m   */
  float position_z; /* m   */
  float velocity_x; /* m/s */
  float velocity_y; /* m/s */
  float velocity_z; /* m/s */
  float mass;       /* kg  */
  float pad;
} Particle;

void Particle_input_arguments(FILE *input);
void Particle_check(Particle *this_particle, char *action, char *routine);
void Particle_pair_check(Particle *this_particle1, Particle *this_particle2,
                         char *action, char *routine);
void Particle_clear(Particle *this_particle);
void Particle_construct(Particle *this_particle);
void Particle_destruct(Particle *this_particle);
void Particle_set_position_randomly(Particle *this_particle);
void Particle_initialize_randomly(Particle *this_particle);
void Particle_initialize(Particle *this_particle);
void Particle_output(FILE *fileptr, Particle *this_particle);
void Particle_output_xyz(FILE *fileptr, Particle *this_particle);
void Particle_array_check(Particle *this_particle_array,
                          int number_of_particles, char *action, char *routine);
Particle *Particle_array_allocate(int number_of_particles);
Particle *Particle_array_construct(int number_of_particles);
Particle *Particle_array_deallocate(Particle *this_particle_array,
                                    int number_of_particles);
Particle *Particle_array_destruct(Particle *this_particle_array,
                                  int number_of_particles);
void Particle_array_initialize_randomly(Particle *this_particle_array,
                                        int number_of_particles);
void Particle_array_initialize(Particle *this_particle_array,
                               int number_of_particles);
void Particle_array_output(char *base_filename, Particle *this_particle_array,
                           int number_of_particles, int timestep);
void Particle_array_output_xyz(FILE *fileptr, Particle *this_particle_array,
                               int number_of_particles);

#endif /* #ifndef nbody_h */
