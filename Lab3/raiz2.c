#include "raiz2.h"
#include <math.h>
#include <stdio.h>

void comparaN(double a, double b, int p, int n){
	double nCalc=log2(2*(b-a)*pow(10,p))-1;
	printf("	Metodo rodado com N: %d iteracoes, esperado %.4g\n", n, nCalc);
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

int falsaposica(double a, double b, int p, double (*f) (double x), double* r){
	double e=0.5*pow(10,-p);
	double c;
	double fc;
	double fa = (*f)(a);
	double fb = (*f)(b);
	int n=0;
	
	while(((b-a)/2)>e){
		c=a-((fa*(b-a))/(fb-fa));
		fc = (*f)(c);
		if(fc<e){
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
	*r = c;
	return n;
}

int newtonraphson(double x0, int p, double (*f) (double x), double (*fl) (double x), double* r){
	double e=0.5*pow(10,-p);
	double fc=100000;
	double fx0 = (*f)(x0);
	double dfx0;
	double c;
	int n=0;
	while(fabs(fc)>=e){
		dfx0 = (*fl)(x0);
		c=x0-(fx0/dfx0);
		fc=(*f)(c);
		x0=c;
		fx0=fc;
		n++;	
	}
	*r = c;
	return n;
}


