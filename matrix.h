#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "vector.h"

class Matrix {
	public:
		static const int dim=3;
	double m[dim*dim];

	Matrix(double m[dim*dim]);
	Matrix();
	double det();

	void print();

	Vector cramers( Vector *V);
	Matrix colsub(Vector *V, int columnr);

	protected:

};


#endif
