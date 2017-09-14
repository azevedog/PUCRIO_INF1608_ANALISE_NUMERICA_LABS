#include <stdio.h>
#include <math.h>
#include "poly.h"

double f1(double x){
	return 2*x;
}

double f2(double x){
	return (4.0*cos(x)-exp(2.0*x));
}

double f3(double x){
	return cos(x);
}

void printSamples(Sample* s, int n){
	int i;
	for(i=0; i<n; i++){
		printf("i=%d, xi=%.16g, yi=%.16g\n",i,*((s[i]).x),*((s[i]).y)); 
	}
}

int main (void){
	Sample* s = Chebyshev(6,0.0,M_PI/2,f3);
	printSamples(s, 6);

	double* den = LagrangeCompute(s);
	printf("Lagrange %.16g\n",LagrangeEval(s, den,M_PI/4 ));

	double* coef = NewtonCompute(s);
	printf("Newton %.16g\n",NewtonEval(s, coef,M_PI/4 ));
	return 42;
}
