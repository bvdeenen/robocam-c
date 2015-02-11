#ifndef SIM_NOISE_H
#define SIM_NOISE_H

void sim_noise(double *v, int N, double noise_level, double res, double pulse_start);
double frand(double lo, double hi);

void write_array(double *w, int N, char* name);


#endif
