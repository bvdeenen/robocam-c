#include <math.h>
#include <stdio.h>

#include "rect.h"
#include "pol.h"

const double pi = 4.0*atan(1.0);

void xy2rp(double x,double y, double &r, double &phi)
{
	r=sqrt(x*x+y*y);
	if(fabs(x)<1e-8){
		if(y>0) phi = 0.5 * pi;
		else phi = 1.5 * pi;
		return;
	}
	phi = atan(y/x);
	if(x<0)
		phi+=pi;

}

char * Rect::print()
{
	snprintf(debug, sizeof(debug), "x=%g, y=%g, z=%g",
		x,y,z);
	return debug;
}


Pol Rect::R2P()
{
	Pol pol;
	double r0;
	pol.r = Len();
	if(pol.r < 1e-8)
		return pol;
	xy2rp(x,y, r0, pol.phi);
	pol.theta = asin(z/pol.r);

	return pol;
}

void Rect::Set(double x, double y, double z)
{
	this->x= x; this->y=y; this->z=z;
}

Rect Rect::Add(Rect *other)
{
	Rect r = *this;
	r.x += other->x;
	r.y += other->y;
	r.z += other->z;
	return r;
}	

void Rect::Invert()
{
	x = -x;
	y = -y;
	z = -z;
}

Rect Rect::Subtract(Rect *other)
{
	Rect r=*other;
	r.Invert();
	return Add(&r);
}
double Rect::Len()
{
	return sqrt(x*x + y*y +z*z);
}

Rect::Rect()
{
}
Rect::Rect(double x, double y, double z)
{
	this->x=x;
	this->y=y;
	this->z=z;
}
