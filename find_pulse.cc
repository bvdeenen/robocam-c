#include <strings.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <assert.h>

#include "find_pulse.h"


double correlate(int i, int dly){
	return -1 + 2 * (((i+dly)/18)&1);
}


void write_array(double *w, char* name, int N){
	int i;
	FILE *f;
	f=fopen(name,"w");
	assert(f);
	for(i=0;i<N;i++)
		fprintf(f,"%g\n", w[i]);

	fclose(f);
}

#define WRITE_ARRAY(w,N) write_array(w, #w".txt" , N)

int statistics(double *w, int N, int span, double *max, double *average, double *w_smooth){
	int	max_pos;
	double span_max=0;
	double prev0;
	int i,j;

	assert((span*2+1)<N);
	*average=0;

	if ( w_smooth != NULL)
		memset(w_smooth, 0, sizeof(double)*N);

	for(i=0;i<span*2+1;i++){
		span_max += w[i];
		*average+=w[i];
	}
	*max = span_max;
	max_pos=i-span-1;
	if ( w_smooth != NULL) w_smooth[i-span-1]=span_max/(2*span+1);



	j=0;
	for(;i<N;i++, j++){
		*average+=w[i];
		span_max -= w[j];
		span_max +=w[i];

		if ( w_smooth != NULL) w_smooth[i-span]=span_max/(2*span+1);

		if ( span_max > *max){
			*max=span_max;
			max_pos=i-span;
		}
	}
	return max_pos;
}

int find_pulse (double * rec_pulse, int N)
{
	int i;
	int dly;
	int max_dly;
	double max;
	double average, max_average;
	int max_pos;

	double cor[N];
	double smooth[N];
	double smoother[N];


	max_dly=0;
	max_average=-1e30;

	for(dly=0;dly<36;dly++){
		for(i=0;i<N;i++){ 
			cor[i]=rec_pulse[i]* correlate(i,dly);
		}
		max_pos = statistics(cor,N, 72, &max, &average, NULL);
		if(average > max_average) {
			max_average=average;
			max_dly=dly;
		}
	}
	for(i=0;i<N;i++){
		cor[i]=rec_pulse[i]* correlate(i,max_dly);
	}

	WRITE_ARRAY(cor, N);
	max_pos = statistics(cor,N, 900, &max, &average, smooth);
	WRITE_ARRAY(smooth, N);
	max_pos = statistics(smooth,N, 500, &max, &average, smoother);
	WRITE_ARRAY(smoother, N);
	return max_pos;
	return EXIT_SUCCESS;
}
