#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "rect.h"
#include "pol.h"
#include "sonar.h"
#include "matrix.h"
#include "vector.h"

#include "sim_noise.h"
#include "find_pulse.h"


#define WRITE_ARRAY(w, N) write_array(w,N,  #w".txt" )

int main (int argc, char *argv[])
{
	Pol pol, pol1;
	Rect rect, rect1, rect2;
	
	srandom(time(NULL));
	Sonar s(0.1, 0.15);


	Pol targetP;
	Rect targetR;
	Vector ranges;
	Rect solution;

	Rect err;

	double res=1e-4;
	double max_range=5;
	double noise_level = 0.5;

	const int N=(int)floor(max_range/res+2000);
	double pulse1[N];
	double pulse2[N];
	double pulse3[N];
	double range1, range2, range3;
	int iterations=1;

	if(argc>1)
		iterations=atoi(argv[1]);
	if(argc>2)
		noise_level=strtod(argv[2], NULL);

	printf("****** noise_level=%g **********\n", noise_level);

	for(int i =0;i<iterations;i++){


		//targetP.Set(20.0, 0.01, M_PI/2 + 0.01);
		targetP.Set(frand(1,max_range), 
				frand(-M_PI/8.0,M_PI/8.0),
				frand(0,M_PI/8.0));
		targetR=targetP.P2R();

		ranges = s.Range(&targetP);

		sim_noise(pulse1,N, noise_level, res, ranges.v[0]);
		sim_noise(pulse2,N, noise_level, res, ranges.v[1]);
		sim_noise(pulse3,N, noise_level, res, ranges.v[2]);
		WRITE_ARRAY(pulse1,N);
		WRITE_ARRAY(pulse2,N);
		WRITE_ARRAY(pulse3,N);
		
		range1=find_pulse(pulse1,N);
		range2=find_pulse(pulse2,N);
		range3=find_pulse(pulse3,N);

		range1 =res * (range1 - 25*36);
		range2 =res * (range2 - 25*36);
		range3 =res * (range3 - 25*36);
		Vector found_ranges(range1,range2,range3);
		//Vector found_ranges( 1.4026,1.3468,1.2277);
		solution = s.Solve( &found_ranges);

		err=targetR.Subtract(&solution);

		Pol found_target = solution.R2P();

		
		double d_theta=found_target.theta-targetP.theta;
		double d_phi=found_target.phi-targetP.phi;

		double angle_error=180*sqrt(pow(d_theta,2)+pow(d_phi,2))/M_PI;

		double l = err.Len();
		//if(l>0.001){
			printf("++++++++++++ i=%d +++++++++++\n",i);

			printf("error length = %.0fmm\n", l*1000);
			printf("error angle  = %.0fdegrees\n", angle_error);
			
			printf("real ranges:  ");ranges.print();
			printf("found ranges: ");found_ranges.print();
			printf("targetP      =%s\n", targetP.print());

			printf("targetR      =%s\n", targetR.print());
			printf("solution     = %s\n", solution.print());
		//} 
		//if(i%1000==0)
			//printf("i=%d\n",i);
	}

}
