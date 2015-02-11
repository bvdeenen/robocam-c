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


int main (int argc, char *argv[])
{
	FILE *fin;
	char buf[50];
	int i, max_pos, N;
	double *rec_pulse;

	assert(argc>1);
	N=atoi(argv[1]);

	rec_pulse=(double*)calloc(N, sizeof(double));

	fin=fopen("rec_pulse.txt","r");
	assert(fin);
	i=0;
	while(fgets(buf,sizeof(buf), fin)){
		assert(i<N);
		rec_pulse[i]=strtod(buf,NULL);
		i++;
	}
	fclose(fin);
	max_pos = find_pulse(rec_pulse,N);
	printf("%d\n", max_pos);
	return EXIT_SUCCESS;
}
