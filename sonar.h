#ifndef _SONAR_H_
#define _SONAR_H_

#include "rect.h"
#include "vector.h"

class Pol;

class	Sonar {
	public:
	
		static const int arms_ct = 3;
		double x_arm, y_arm;
		Sonar(double w, double h);
		Vector Range(Pol *target);
		Rect Solve(Vector *);
		Rect Solve(double l1, double l2, double l3);
		inline double sqr(double v){return v*v;};
		void print();
};	


#endif
