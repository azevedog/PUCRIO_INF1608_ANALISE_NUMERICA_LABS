#include "raiz2.h"
#include <stdio.h>
#include <math.h>

double reta(double x){
	return -1.0+x;
}


double funcDeTeste2(double x){
	return -2.5/(-x+1.8);
}

double funcDeTeste(double x){
	return sin(x)-pow(x,3);
}

double funcParaquedista(double x){
	return ((9.8*x*(1-exp((-15*9)/x)))/15)-35;
}

double derivadafuncDeTeste(double x){
	return cos(x)-3*pow(x,2);
}

int bissecao(double a, double b, int p, double (*f) (double x), double* r){
	double e=0.5*pow(10,-p);
	double c;
	double fc;
	double fa = (*f)(a);
	int n=0;
	
	while(((b-a)/2)>e){
		c=(a+b)/2.0;
		fc = (*f)(c);
		if(fc==0.0){
			break;
		}
		if(fa*fc<0){
			b=c;
		}else{
			a=c;
			fa=fc;
		}
		n++;
	}
	*r = c;
	return n;
	
}

int main(void){
	double raiz1;
	double raiz2;
	double raiz3;

	printf("INICIO\n");
	int n1 = bissecao (0.5, 1.5, 6, funcDeTeste, &raiz1);
	printf("	A raiz pelo método da bissecao eh: %.16g\n", raiz1);
	comparaN(0.5, 1.5, 6, n1);
	int n2 = falsaposica (0.5, 1.5, 6, funcDeTeste, &raiz2);
	printf("	A raiz pelo método da falsa posicao eh: %.16g\n", raiz2);
	comparaN(0.5, 1.5, 6, n2);
	int n3 = newtonraphson (1.5, 6, funcDeTeste,derivadafuncDeTeste, &raiz3);
	printf("	A raiz pelo método da newtonraphson eh: %.16g\n", raiz3);
	comparaN(0.5, 1.5, 6, n3);
	printf("FIM\n");
	return 42;	
}
