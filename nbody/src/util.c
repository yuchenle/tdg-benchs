#include "nbody.h"

const int default_string_length = DEFAULT_STRING_LENGTH;
const int server = 0;
char base_filename[DEFAULT_STRING_LENGTH + 1];
float domain_size_x;
float domain_size_y;
float domain_size_z;
float time_interval;
int number_of_particles;
int number_of_timesteps;
int timesteps_between_outputs;
unsigned int random_seed;

void Particle_input_arguments(FILE *input) {
  number_of_particles = default_number_of_particles;
  domain_size_x = default_domain_size_x;
  domain_size_y = default_domain_size_y;
  domain_size_z = default_domain_size_z;
  time_interval = default_time_interval;
  number_of_timesteps = default_number_of_timesteps;
  timesteps_between_outputs = default_timesteps_between_outputs;
  random_seed = default_random_seed;
  mass_maximum = default_mass_maximum;

  if (fscanf(input, "%d", &number_of_particles) != 1) {
    fprintf(stderr,
            "ERROR: cannot read number of particles from standard input!\n");
    exit(program_failure_code);
  }

  if (number_of_particles < 1) {
    fprintf(stderr, "ERROR: cannot have %d particles!\n", number_of_particles);
    exit(program_failure_code);
  }

  if (number_of_particles == 1) {
    fprintf(stderr, "There is only one particle, therefore no forces.\n");
    exit(program_failure_code);
  }

  if (fscanf(input, "%f", &domain_size_x) != 1) {
    fprintf(stderr, "ERROR: cannot read domain size X from standard input!\n");
    exit(program_failure_code);
  }

  if (domain_size_x <= 0.0) {
    fprintf(stderr,
            "ERROR: cannot have a domain whose X dimension has length %f!\n",
            domain_size_x);
    exit(program_failure_code);
  }

  if (fscanf(input, "%f", &domain_size_y) != 1) {
    fprintf(stderr, "ERROR: cannot read domain size Y from standard input!\n");
    exit(program_failure_code);
  }

  if (domain_size_y <= 0.0) {
    fprintf(stderr,
            "ERROR: cannot have a domain whose Y dimension has length %f!\n",
            domain_size_y);
    exit(program_failure_code);
  }

  if (fscanf(input, "%f", &domain_size_z) != 1) {
    fprintf(stderr, "ERROR: cannot read domain size Z from standard input!\n");
    exit(program_failure_code);
  }

  if (domain_size_z <= 0.0) {
    fprintf(stderr,
            "ERROR: cannot have a domain whose Z dimension has length %f!\n",
            domain_size_z);
    exit(program_failure_code);
  }

  if (fscanf(input, "%f", &time_interval) != 1) {
    fprintf(stderr, "ERROR: cannot read time interval from standard input!\n");
    exit(program_failure_code);
  }

  if (time_interval <= 0.0) {
    fprintf(stderr, "ERROR: cannot have a time interval of %f!\n",
            time_interval);
    exit(program_failure_code);
  }

  if (fscanf(input, "%d", &number_of_timesteps) != 1) {
    fprintf(stderr,
            "ERROR: cannot read number of timesteps from standard input!\n");
    exit(program_failure_code);
  }

  if (number_of_timesteps <= 0) {
    fprintf(stderr, "ERROR: cannot have %d timesteps!\n", number_of_timesteps);
    exit(program_failure_code);
  }

  if (fscanf(input, "%d", &timesteps_between_outputs) != 1) {
    fprintf(
        stderr,
        "ERROR: cannot read timesteps between outputs from standard input!\n");
    exit(program_failure_code);
  }

  if (timesteps_between_outputs <= 0) {
    fprintf(stderr, "ERROR: cannot have %d timesteps between outputs!\n",
            timesteps_between_outputs);
    exit(program_failure_code);
  }

  if (fscanf(input, "%d", &random_seed) != 1) {
    fprintf(stderr, "ERROR: cannot read random seed from standard input!\n");
    exit(program_failure_code);
  }

  if (fscanf(input, "%f", &mass_maximum) != 1) {
    fprintf(stderr, "ERROR: cannot read mass maximum from standard input!\n");
    exit(program_failure_code);
  }

  if (mass_maximum <= 0.0) {
    fprintf(stderr, "ERROR: cannot have a maximum mass of %f!\n", mass_maximum);
    exit(program_failure_code);
  }

  fgetc(input);
  fgets(base_filename, default_string_length, input);
  if (base_filename[strlen(base_filename) - 1] == '\n') {
    base_filename[strlen(base_filename) - 1] = '\0';
  }
}

#ifdef CHECK
void Particle_check(Particle *this_particle, char *action, char *routine) {
  if (this_particle != (Particle *)NULL) {
    return;
  }

  fprintf(stderr, "ERROR: can't %s a nonexistent particle\n",
          ((action == (char *)NULL) || (strlen(action) == 0))
              ? "perform an unknown action on"
              : action);
  fprintf(stderr, "  in %s\n",
          ((routine == (char *)NULL) || (strlen(routine) == 0))
              ? "an unknown routine"
              : routine);

  exit(program_failure_code);
}

void Particle_pair_check(Particle *this_particle1, Particle *this_particle2,
                         char *action, char *routine) {
  if ((this_particle1 != (Particle *)NULL) &&
      (this_particle2 != (Particle *)NULL))
    return;
}

fprintf(stderr, "ERROR: can't %s\n",
        ((action == (char *)NULL) || (strlen(action) == 0))
            ? "perform an unknown action on"
            : action);

if (this_particle1 == (Particle *)NULL) {
  if (this_particle2 == (Particle *)NULL) {
    fprintf(stderr, "  a pair of nonexistent particles\n");
  } else {
    fprintf(stderr, "  a nonexistent particle and an existing particle\n");
  }
} else {
  fprintf(stderr, "  an existing particle and a nonexistent particle\n");
}

fprintf(stderr, "  in %s\n",
        ((routine == (char *)NULL) || (strlen(routine) == 0))
            ? "an unknown routine"
            : routine);

exit(program_failure_code);
}
#endif

void Particle_clear(Particle *this_particle) {
#ifdef CHECK
  Particle_check(this_particle, "clear", "Particle_clear");
#endif

  this_particle->position_x = 0.0;
  this_particle->position_y = 0.0;
  this_particle->position_z = 0.0;
  this_particle->velocity_x = 0.0;
  this_particle->velocity_y = 0.0;
  this_particle->velocity_z = 0.0;
  this_particle->mass = 0.0;
}

void Particle_construct(Particle *this_particle) {
#ifdef CHECK
  Particle_check(this_particle, "construct", "Particle_construct");
#endif

  Particle_clear(this_particle);
}

void Particle_destruct(Particle *this_particle) {
#ifdef CHECK
  Particle_check(this_particle, "destruct", "Particle_destruct");
#endif

  Particle_clear(this_particle);
}

void Particle_set_position_randomly(Particle *this_particle) {
#ifdef CHECK
  Particle_check(this_particle, "randomly set the position",
                 "Particle_set_randomly");
#endif

  this_particle->position_x =
      domain_size_x * ((float)random() / ((float)RAND_MAX + 1.0));
  this_particle->position_y =
      domain_size_y * ((float)random() / ((float)RAND_MAX + 1.0));
  this_particle->position_z =
      domain_size_z * ((float)random() / ((float)RAND_MAX + 1.0));
}

void Particle_initialize_randomly(Particle *this_particle) {
#ifdef CHECK
  Particle_check(this_particle, "randomly initialize",
                 "Particle_initialize_randomly");
#endif

  Particle_clear(this_particle);
  Particle_set_position_randomly(this_particle);
  this_particle->mass =
      mass_maximum * ((float)random() / ((float)RAND_MAX + 1.0));

#ifdef CHECK_VAL
  printf("mass %g\n", this_particle->mass);
#endif
}

void Particle_initialize(Particle *this_particle) {
#ifdef CHECK
  Particle_check(this_particle, "initialize", "Particle_initialize");
#endif

  Particle_initialize_randomly(this_particle);
}

void Particle_output(FILE *fileptr, Particle *this_particle) {
  fprintf(fileptr, "%g %g %g %g %g %g %g\n", this_particle->position_x,
          this_particle->position_y, this_particle->position_z,
          this_particle->velocity_x, this_particle->velocity_y,
          this_particle->velocity_z, this_particle->mass);
}

void Particle_output_xyz(FILE *fileptr, Particle *this_particle) {
  fprintf(fileptr, "C %g %g %g\n", this_particle->position_x,
          this_particle->position_y, this_particle->position_z);
}

#ifdef CHECK
void Particle_array_check(Particle *this_particle_array,
                          int number_of_particles, char *action,
                          char *routine) {
  if (number_of_particles < 0) {
    fprintf(stderr, "ERROR: illegal number of particles %d\n",
            number_of_particles);
    fprintf(stderr, "  to %s\n",
            ((action == (char *)NULL) || (strlen(action) == 0))
                ? "perform an unknown action on"
                : action);
    fprintf(stderr, "  in %s\n",
            ((routine == (char *)NULL) || (strlen(routine) == 0))
                ? "an unknown routine"
                : routine);

    exit(program_failure_code);
  }

  if (number_of_particles == 0) {
    if (this_particle_array == (Particle *)NULL) {
      return (Particle *)NULL;
    }

    fprintf(stderr, "ERROR: can't %s\n",
            ((action == (char *)NULL) || (strlen(action) == 0))
                ? "perform an unknown action on"
                : action);
    fprintf(stderr, "  an existing particle array of length 0\n");
    fprintf(stderr, "  in %s\n",
            ((routine == (char *)NULL) || (strlen(routine) == 0))
                ? "an unknown routine"
                : routine);

    exit(program_failure_code);
  }

  if (this_particle_array == (Particle *)NULL) {
    fprintf(stderr, "ERROR: can't %s\n",
            ((action == (char *)NULL) || (strlen(action) == 0))
                ? "perform an unknown action on"
                : action);
    fprintf(stderr, "  a nonexistent array of %d particles\n",
            number_of_particles);
    fprintf(stderr, "  in %s\n",
            ((routine == (char *)NULL) || (strlen(routine) == 0))
                ? "an unknown routine"
                : routine);

    exit(program_failure_code);
  }
}
#endif

Particle *Particle_array_allocate(int number_of_particles) {
  Particle *this_particle_array = (Particle *)NULL;

#ifdef CHECK
  if (number_of_particles < 0) {
    fprintf(stderr, "ERROR: illegal number of particles %d to allocate\n",
            number_of_particles);
    fprintf(stderr, "  in Particle_array_construct\n");

    exit(program_failure_code);
  }
#endif

  if (number_of_particles == 0) {
    return (Particle *)NULL;
  }

  // cudaMallocManaged( (void **) &this_particle_array, sizeof(Particle) *
  // number_of_particles, cudaMemAttachGlobal);
  this_particle_array =
      (Particle *)malloc(sizeof(Particle) * number_of_particles);

  if (this_particle_array == (Particle *)NULL) {
    fprintf(stderr, "ERROR: can't allocate a particle array of %d particles\n",
            number_of_particles);
    fprintf(stderr, "  in Particle_array_construct\n");

    exit(program_failure_code);
  }

  return this_particle_array;
}

Particle *Particle_array_construct(int number_of_particles) {
  Particle *this_particle_array = (Particle *)NULL;
  int index;

  this_particle_array = Particle_array_allocate(number_of_particles);

  for (index = 0; index < number_of_particles; index++) {
    Particle_construct(&(this_particle_array[index]));
  }

  return this_particle_array;
}

Particle *Particle_array_deallocate(Particle *this_particle_array,
                                    int number_of_particles) {
#ifdef CHECK
  Particle_array_check(this_particle_array, number_of_particles, "deallocate",
                       "Particle_array_deallocate");
#endif

  // cudaFree(this_particle_array);
  free(this_particle_array);

  this_particle_array = (Particle *)NULL;

  return (Particle *)NULL;
}

Particle *Particle_array_destruct(Particle *this_particle_array,
                                  int number_of_particles) {
  int index;

#ifdef CHECK
  Particle_array_check(this_particle_array, number_of_particles, "destroy",
                       "Particle_array_destruct");
#endif

  for (index = number_of_particles - 1; index >= 0; index--) {
    Particle_destruct(&(this_particle_array[index]));
  }

  return Particle_array_deallocate(this_particle_array, number_of_particles);
}

void Particle_array_initialize_randomly(Particle *this_particle_array,
                                        int number_of_particles) {
  int index;

#ifdef CHECK
  Particle_array_check(this_particle_array, number_of_particles,
                       "initialize randomly",
                       "Particle_array_initialize_randomly");
#endif

  for (index = 0; index < number_of_particles; index++) {
    Particle_initialize_randomly(&(this_particle_array[index]));
  }
}

void Particle_array_initialize(Particle *this_particle_array,
                               int number_of_particles) {
  Particle_array_initialize_randomly(this_particle_array, number_of_particles);
}

void Particle_array_output(char *base_filename, Particle *this_particle_array,
                           int number_of_particles, int timestep) {
  FILE *fileptr = (FILE *)NULL;
  char *filename = (char *)NULL;
  int filename_length;
  int index;

#ifdef CHECK
  Particle_array_check(this_particle_array, number_of_particles, "output",
                       "Particle_array_output");
#endif

  filename_length = strlen(base_filename) + 1 + 8 + 1 + 3;

  filename = (char *)malloc(sizeof(char) * (filename_length + 1));

  if (filename == (char *)NULL) {
    fprintf(stderr, "ERROR: can't allocate the filename string\n");
    fprintf(stderr, "  %s_%8.8d.txt\n", base_filename, timestep);
    fprintf(stderr, "  in Particle_array_output\n");

    exit(program_failure_code);
  }

  sprintf(filename, "%s_%8.8d.txt", base_filename, timestep);

  fileptr = fopen(filename, "w");

  if (fileptr == (FILE *)NULL) {
    fprintf(stderr, "ERROR: can't open the output file named\n");
    fprintf(stderr, "  %s\n", filename);
    fprintf(stderr, "  in Particle_array_output\n");

    exit(program_failure_code);
  }

  fprintf(fileptr, "%d %d %d %g %g %g %g %g %d\n", number_of_particles,
          number_of_timesteps, timesteps_between_outputs, domain_size_x,
          domain_size_y, domain_size_z, mass_maximum, time_interval,
          random_seed);

  fprintf(fileptr, "%d\n", timestep);

  for (index = 0; index < number_of_particles; index++) {
    Particle_output(fileptr, &(this_particle_array[index]));
  }

  if (fclose(fileptr) != 0) {

    fprintf(stderr, "ERROR: can't close the output file named\n");
    fprintf(stderr, "  %s\n", filename);
    fprintf(stderr, "  in Particle_array_output\n");

    exit(program_failure_code);
  }

  fileptr = (FILE *)NULL;

  free(filename);
  filename = (char *)NULL;
}

void Particle_array_output_xyz(FILE *fileptr, Particle *this_particle_array,
                               int number_of_particles) {

  fprintf(fileptr, "%d\nNBody\n", number_of_particles);

  int index;
  for (index = 0; index < number_of_particles; index++) {
    Particle_output_xyz(fileptr, &(this_particle_array[index]));
  }
}
