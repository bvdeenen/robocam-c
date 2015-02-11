#include <math.h>
#include <string.h>
#include <stdio.h>

#include "sonar.h"
#include "pol.h"
#include "rect.h"
#include "matrix.h"


Vector Sonar::Range(Pol *target)
{
	Vector ranges;
	Rect targetR, r;
	targetR = target->P2R();
	Rect arm;
	for(int i=0;i<arms_ct;i++){
		r=targetR;
		switch(i){
			case 0:
				arm.Set(x_arm,0,0); break;
			case 1:
				arm.Set(-x_arm,0,0); break;
			case 2:
				arm.Set(0,y_arm,0); break;
		}
		r=r.Subtract(&arm);
		ranges.v[i] = r.Len();
	}

	return ranges;
}

Rect Sonar::Solve(double l1, double l2, double l3)
{
	Vector v(l1,l2,l3);
	return Solve(&v);
}
Rect Sonar::Solve(Vector *l)
{
	// this equation uses the fact that the first two sensors are by
	// definition on the x axis, symmetrical around the origin.
	// The third sensor is on the y axis.
	double x,y,z;
	//printf("x_arm=%g, y_arm=%g, l=", x_arm, y_arm); l->print();
	x = (sqr(l->v[0])-sqr(l->v[1]))/(-4.0*x_arm);

	y = ( sqr(l->v[2]) - sqr(l->v[1]) + 2 * x * x_arm + sqr(x_arm) -
			sqr(y_arm))/(-2.0*y_arm);

	// this is the mathematically correct solution
	// z=sqrt(sqr(l->v[2])-sqr(x)-sqr(y-y_arm));
	//
	// however, we need to be able to work with real world noise values, so
	// we'll just use the average of the three ranges
	
	z=(l->v[0] + l->v[1] + l->v[2])/3.0;

	Rect solution(x,y,z);
	return solution;
}

Sonar::Sonar(double w, double h)
{
	this->x_arm=w;
	this->y_arm=h;
}

void Sonar::print()
{
	printf("x_arm = %f\n", x_arm);
	printf("y_arm = %f\n", y_arm);
}
