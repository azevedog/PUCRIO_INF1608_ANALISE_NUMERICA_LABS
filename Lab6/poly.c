#include <stdlib.h>
#include <math.h>
#include "poly.h"
#include <stdio.h>

Sample* newSamples(int n){
	Sample* s = (Sample*)malloc(sizeof(Sample)*n);
	s->n = n;
	return s;
}

/**
n - número de amostras
[a,b] - intervalo das amostras
f* - função para cálculo do Yi dados os Xi determinados pelo Teorema de Chebyshev.
*/
Sample* Chebyshev(int n, double a, double b, double (*f)(double x)){	
	int i;
	int beta =1;
	double temp1 = (b-a)/2;
	double temp2 = (b+a)/2;
	Sample* s = newSamples(n);

	for(i=0; i<n; i++){
		s[i].n=i;
		s[i].x = (double*)malloc(sizeof(double)); 
		*(s[i].x) = temp1*(cos((beta*M_PI)/(2.0*n)))+temp2;
		s[i].y = (double*)malloc(sizeof(double)); 
		*((s[i]).y)= (*f)(*(s[i].x));
		beta+=2;
	}
	return s;
}

double* LagrangeCompute(Sample* s){
	int i,j,n = s[0].n;
	double* denom = (double*)malloc(sizeof(double)*n);

	for (i=0; i<n; i++){
		denom[i] = 0;
		for(j=0; j<n;j++){
			if(j!=i){
				denom[i] *= (*(s[i].x))-(*(s[j].x)); 
			}
		}	
	} 
	return denom;
}

double* LagrangeNum(Sample* s, double x){
	int i,j,n = s[0].n;
	double* nume = (double*)malloc(sizeof(double)*n);

	for (i=0; i<n; i++){
		nume[i] = 0;
		for(j=0; j<n;j++){
			if(j!=i){
				nume[i] *= x-(*(s[j].x)); 
			}
		}	
	} 
	return nume;
}

double LagrangeEval(Sample* s, double* den, double x){
	double Px = 0;
	int i,n = s[0].n;
	double* nume = LagrangeNum(s, x);
	
	for (i=0; i<n; i++){
		Px+=(*(s[i].y))*(nume[i]/den[i]);
	}
	return Px;
}

double* fastNewtonCoef(int i, int j, double** m, Sample* s){
	if(m[i][j]==-HUGE_VALL){
		m[i][j]= (fastNewtonCoef(i+1, j,m,s)-fastNewtonCoef(i,j-1,m,s))/(*(s[j].x)-*(s[i].x));
	}
	return &m[i][j];	
		
}

double* NewtonCompute(Sample* s){
	int i,j,n = s[0].n;	
	double m[n][n];
	double* coef = (double*)malloc(sizeof(double)*n);
	for (i=0; i<n; i++){
		for(j=0; j<n;j++){	
			if(i==j){
				m[i][j]=*(s[i].y);
			}else{
				m[i][j]=-HUGE_VALL;	
			}
		}
	}

	for(i=0; i<n;i++){
		coef[i] = *fastNewtonCoef(0,i, m,s);
	}
	return coef;	

}

double NewtonEval(Sample* s, double* coef, double x){
	int i,j,n = s[0].n;
	double val=0, aux=0;
	for(i=0; i<n;i++){
		aux=coef[i];
		for(j=i-1; j>=0; j--){
			aux*=x-*(s[j].x);
		}
		val+=aux;
	}
	return val;
}
