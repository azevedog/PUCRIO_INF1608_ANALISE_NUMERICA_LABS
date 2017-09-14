#include "raiz.h"
#include <math.h>
#include <stdio.h>

void comparaN(double a, double b, int p, int n){
	double nCalc=log2(2*(b-a)*pow(10,p))-1;
	printf("	Bissecao rodada com N: %d iteracoes, esperado %.4g\n", n, nCalc);
}

double bissecao(double a, double b, int p, double (*f) (double x)){
	double oA = a;
	double oB = b;
	double e=0.5*pow(10,-p);
	double c;
	double fc;
	double fa = (*f)(a);
	double fb = (*f)(b);
	int n=0;
	
	while(((b-a)/2)>e){
		c=(a+b)/2.0;
		fc = (*f)(c);
		if(fc==0.0){
			break;
		}
		if(fa*fc<0){
			b=c;
			fb=fc;
		}else{
			a=c;
			fa=fc;
		}
		n++;
	}
	comparaN(oA, oB, p, n);
	return c;
	
}

double pontofixo(double x0, double epsilon, double (*g) (double x)){
	double x=x0;
	double y=(*g)(x);
	int n=0;
	while(fabs(y-x)>epsilon){
		x=y;
		y=(*g)(x);
		n++;
	}
	printf("	PontoFixo rodado com N: %d iteracoes\n", n);
	return x;
	
}

