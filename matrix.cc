#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "matrix.h"


double Matrix::det()
{
	int r,c,c1,p,i;

	double f=0,d=0;
	for(c=0;c<dim;c++){
		f=1.0;
		for(r=0;r<dim;r++){
			c1=c+r;
			if(c1>=dim) c1-=dim;
			f*= this->m[dim*r + c1];
		}
		d+=f;
	}
	for(c=0;c<dim;c++){
		f=1.0;
		for(r=0;r<dim;r++){
			c1=c-r;
			if(c1<0) c1+=dim;
			f *= this->m[dim*r + c1];
		}
		d -=f;
	}
	return d;
}

Matrix::Matrix()
{
}

Matrix::Matrix(double m[9])
{
	for(int i=0;i<dim*dim;i++)
		this->m[i] = m[i];
}

void Matrix::print()
{
	int r, c;
	for(r=0;r<dim;r++){
		printf("|");
		for(c=0;c<dim;c++)
			printf("%6.3f", m[r*dim+c]);
		printf("|\n");
	}

}

Vector Matrix::cramers( Vector *V)
{
	int r;
	Vector result;
	Matrix sub;
	double nominator = this->det();
	printf("Cramers ******* nominator = %g\n", nominator);
	assert(nominator!=0);
	for(r=0;r<dim;r++){
		sub=this->colsub(V,r);
		sub.print();
		printf("det sub=%g\n", sub.det());
		result.v[r]=sub.det()/nominator;
	}
	return result;
}

Matrix Matrix::colsub(Vector *V, int columnr)
{
	Matrix res = *this;
	assert(columnr>=0 && columnr<dim);
	for(int r=0;r<dim;r++)
		res.m[r*dim+columnr] = V->v[r];
	return res;
}
