#ifndef _RECT_H_
#define _RECT_H_

class Pol;

class Rect {
	public:
		char *print();
		double x,y,z;

		Rect(double,double,double);
		Rect();
		Rect Add(Rect *other);
		Rect Subtract(Rect *other);
		void Invert();
		double Len();
		void Set(double x, double y, double z);
		Pol	R2P();
	protected:
		char	debug[100];
};

#endif
