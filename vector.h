#ifndef _VECTOR_H_
#define _VECTOR_H_

class Vector {
	public:
		static const int dim=3;
	double v[dim];
	Vector(double v[dim]);
	Vector();
	Vector(double,double,double);
	void print();
};

#endif
