#include <stdio.h>

#include "vector.h"

Vector::Vector()
{
}

Vector::Vector(double x, double y, double z)
{
	v[0]=x; v[1]=y; v[2]=z;
}
Vector::Vector(double v[dim])
{
	for(int i =0; i<dim;i++)
		this->v[i]=v[i];
}

void Vector::print()
{
	printf("|");
	for(int r=0;r<dim;r++)
		printf("%g,", this->v[r]);
	printf("|\n");
}

