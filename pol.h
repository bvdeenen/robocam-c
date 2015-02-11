#ifndef _POL_H_
#define _POL_H_

class Rect;


class Pol {
	public:
		Pol(void);
		double r, phi, theta;
		void Set(double r, double phi, double theta);
		char *print();
		void Invert();
		double Len();
	Rect P2R();
	protected:
		char	debug[100];
};

#endif
