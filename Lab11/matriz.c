#include <stdlib.h>
#include "matriz.h"
#include <stdio.h> 

double** mat_cria(int m, int n){
	int i;
	double** line = (double**) malloc(sizeof(double*)*m);
	for(i=0; i<m; i++){
		line[i]= (double*) malloc(sizeof(double)*n);
	}
	return line;
}

void mat_libera(int m, double** A){
	int i;
	for(i=0; i<m; i++){
		free(A[i]);
	}
};

void mat_transposta (int m, int n, double** A, double** T){
	int i, j;
	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			T[j][i] = A[i][j];
		}
	}
	
}

void zeraVetor(double* w, int m){
	int j;
	for(j=0; j<m; j++){
		w[j]=0;
	}
}

void mat_multv(int m, int n, double** A, double* v, double* w){
	int i, j;
	zeraVetor(w,m);
	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			w[i]+=A[i][j]*v[j];
		}
	}
}

void mat_multm(int m, int n, int q, double** A, double** B, double** C){
	int i, j,k;
	for(i=0; i<m; i++){
		for(k=0; k<q; k++){
			for(j=0; j<n; j++){
				C[i][k]+=A[i][j]*B[j][k];
			}
		}
	}
}

void mat_somam(int m, int n, int q, double** A, double** B, double** C){
	int i, j,k;
	for(i=0; i<m; i++){
		for(k=0; k<q; k++){
			for(j=0; j<n; j++){
				C[i][k]+=A[i][j]+B[j][k];
			}
		}
	}
}

void mat_multEscalar(int m, int n, double** A, double escalar){
	int i, j;
	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			A[i][j]= A[i][j]*escalar;
		}
	}
}
 
double** geraIdentQuadrada(int n){
	double** ident = mat_cria(n,n);
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j){
				ident[i][j]=1.0;
			}else{
				ident[i][j]=0.0;
			}
		}
	}
	return ident;
}
