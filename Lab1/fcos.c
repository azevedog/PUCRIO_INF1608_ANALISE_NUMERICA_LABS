#include <math.h>

double fcos(double x){
	double term = x-M_PI/2;
	return term*(-1+((term*term)/6));
}