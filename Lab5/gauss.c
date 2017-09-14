#include "gauss.h"
#include "matriz.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

double** getPermutacao(int n){
	double** P = mat_cria(n,n);
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j){
				P[i][j]=1.0;
			}else{
				P[i][j]=0;
			}
		}	
	}
	return P;
}

void pivot(int j, int n, double** A, double** P){
	double aux;
	int i,k;
	for(i=j+1;i<n;i++){
		if(abs(A[j][j])<abs(A[i][j])){
			for(k=0; k<n;k++){
				aux=A[i][k];
				A[i][k]=A[j][k];
				A[j][k] = aux;
				aux=P[i][k];
				P[i][k]=P[j][k];
				P[j][k] = aux;
			}
		}
	}
}

double** fatoracao(int n, double** A){
	double** P = getPermutacao(n);
	int i,j,k;
	for(j=0;j<n;j++){
		pivot(j, n, A, P);
		for(i=j+1;i<n;i++){
			A[i][j]=A[i][j]/A[j][j];
		}
		for(i=j+1;i<n;i++){
			for(k=j+1;k<n;k++){
				A[i][k]=A[i][k]-A[j][k]*A[i][j];
			}
		}
	}
	return P;
}



double* substituicao(int n, double** A, double** P, double* b){
	double c[n];
	double w[n];
	double* x = (double*) malloc(sizeof(double)*n);
	int i, j;
	
	mat_multv( n,  n, P, b, w);	

	zeraVetor(c, n);
	c[0]=w[0];
	for(i=1;i<n;i++){
		for(j=0;j<i;j++){
			c[i]+=-A[i][j]*c[j];
		}
		c[i]+=w[i];
	}

	zeraVetor(x, n);
	x[n-1]=c[n-1]/A[n-1][n-1];
	for(i=n-2;i>=0;i--){
		x[i]+=c[i];
		for(j=n-1;j>i;j--){
			x[i]+=-A[i][j]*x[j];
		}
		x[i]=x[i]/A[i][i];
	}
	return x;
}
