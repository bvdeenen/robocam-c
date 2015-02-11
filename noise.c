#include <strings.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <assert.h>




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

double r(double max){
	return ((double)random()/RAND_MAX * 2 * max - max);
}

int main (int argc, char *argv[])
{
	int i;
	int dly;

	double phase;
	int start, end;
	const double PI=3.14159265359;
	double noise_level;
	int N;
	
	double *rec_pulse;

	assert(argc>2);
	srandom(time(NULL));

	noise_level=strtod(argv[1], NULL);
	N=atoi(argv[2]);

	rec_pulse=(double*)calloc(N, sizeof(double));

	start=1500 + random() % (N-3000);
	end=start+50*36;

	printf("%d", (start+end)/2);
	for(i=0;i<N;i++){
		rec_pulse[i]+=r(noise_level);
	}

	for(i=0, phase=0;i<N;i++){
		if(i>=start && i<end){
			rec_pulse[i]+=sin(phase);
			phase+=PI/18;
		}
	}
	
	WRITE_ARRAY(rec_pulse,N);
	return EXIT_SUCCESS;
}
