#include <math.h>
#include <stdio.h>
#include "brent.h"

double f1(double x){
	return (4.0*cos(x)-exp(2.0*x));
}

double f2(double x){
	return (x/2.0)-tan(x);
}

double f3(double x){
	return 1-(x*log(x+20));
}

double f4(double x){
	return pow(2,x)-3.0*x;
}

double f5(double x){
	return pow(x,3)+x-1;
}

int main (void){
	printf("\nINICIO\n");
	printf("Funcao1");
	printf("END Funcao1 - %.16g\n", brent(-1.0,1.0,6,f1));
	printf("Funcao2\n");
	printf("END Funcao2 - %.16g\n", brent(-1.0,1.0,6,f2));
	printf("Funcao3\n");
	printf("END Funcao3 - %.16g\n", brent(-1.0,1.0,6,f3));
	printf("Funcao4\n");
	printf("END Funcao4 - %.16g\n", brent(-1.0,1.0,6,f4));
	printf("Funcao5\n");
	printf("END Funcao5 - %.16g\n", brent(-1.0,1.0,6,f5));
	return 42;
}


