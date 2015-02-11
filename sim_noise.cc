#include <strings.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <assert.h>

#include "sim_noise.h"




void write_array(double *w, int N, char* name){
	int i;
	FILE *f;
	f=fopen(name,"w");
	assert(f);
	for(i=0;i<N;i++)
		fprintf(f,"%g\n", w[i]);

	fclose(f);
}

#define WRITE_ARRAY(w, N) write_array(w,N,  #w".txt" )

double frand(double lo, double hi){
	double r = ((unsigned)random())/(double)RAND_MAX;
	assert(lo!=hi);
	return (lo + r*(hi-lo));
}

void sim_noise(double *rec_pulse, int N, double noise_level, double res, double pulse_start)
{
	int i;
	int dly;

	double phase;
	int start, end;
	const double PI=3.14159265359;
	
	//printf("res=%g, pulse_start=%g, N=%d\n", res,pulse_start, N);
	start=(int)floor(pulse_start/res);
	//printf("start=%d, ", start);
	assert (start<N);
	end=start+50*36;
	//printf("end=%d, ", end);
	assert (end<N);

	for(i=0;i<N;i++){
		rec_pulse[i]=frand(-noise_level, noise_level);
		if(i>=start && i<end){
			rec_pulse[i]+=sin(phase);
			phase+=PI/18;
		}
	}
	
}
