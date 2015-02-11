#include <math.h>
#include <stdio.h>

#include "pol.h"
#include "rect.h"

const double pi = 4.0*atan(1.0);


Rect Pol::P2R()
{
	// convert my polar coordinates to rectangular coordinates
	Rect rect;

	double r0 = this->r * cos(this->theta);

	rect.x = r0 * cos (this->phi);
	rect.y = r0 * sin ( this->phi);
	rect.z = this->r * sin(this->theta);
	return rect;
}

Pol::Pol(void)
{
}

void Pol::Set(double r, double phi, double theta)
{
	this->r = r; 
	this->phi=phi;
	this->theta=theta; 
}


char * Pol::print()
{
	snprintf(debug, sizeof(debug), "r=%.2fm, phi=%.2f(%.0fd), theta=%.2f(%.0fd)",
		r, phi, phi*180/M_PI, theta, theta*180/M_PI);
	return debug;
}
