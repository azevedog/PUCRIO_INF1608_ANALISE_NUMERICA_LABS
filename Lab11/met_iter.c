#include <stdlib.h>
#include "matriz.h"
#include <stdio.h> 
#include <math.h> 

int Jacobi(int n, double** A, double* b, double* x, double tol){
	int i,j, count = 0;
	double norma2;
	double** DI = mat_cria(n,n);
	double** LU = mat_cria(n,n);
	double* aux = malloc(sizeof(double)*n);
	double* aux2 = malloc(sizeof(double)*n);
	
	/*Prepara matrizes*/
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j){
				DI[i][j]=1.0/A[i][j];
				LU[i][j]=0.0;
			}else{
				LU[i][j]=A[i][j];
				DI[i][j]=0.0;
			}
		}
	}
	
	while(1){	
		norma2=0;		
		mat_multv(n, n, LU, x, aux);
		for(i=0; i<n;i++){
			aux[i] = b[i]-aux[i];
		}
		mat_multv(n, n, DI, aux, aux2);
		count++;
		for(i=0; i<n;i++){
			double diff = fabs(aux2[i])-fabs(x[i]);
			norma2 += diff*diff;
			x[i] = aux2[i];
		}
		norma2 = sqrt(norma2);
		if(norma2<=tol) break;
	}
	return count;
}

int GaussSeidel(int n, double** A, double* b, double* x, double tol){
	int i,j,k,count = 0;
	double norma2;
	double** DI = mat_cria(n,n);
	double** L = mat_cria(n,n);
	double** U = mat_cria(n,n);
	double* xAntes = malloc(sizeof(double)*n);

	/*Prepara matrizes*/
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j){
				DI[i][j]=1.0/A[i][j];
				L[i][j]=0.0;
				L[i][j]=0.0;
			}else if(i>j){
				L[i][j]= A[i][j];
				U[i][j]=0.0;
				DI[i][j]=0.0;
			}else{
				U[i][j]= A[i][j];
				L[i][j]=0.0;
				DI[i][j]=0.0;
			}
		}
		xAntes[i]=x[i];
	}

	while(1){
		norma2=0.0;
		for(i=0;i<n;i++){
			double temp1=0, temp2=0;
			for(j=i+1;j<n;j++){
				temp1 += x[j]*U[i][j]; 
			}
			for(k=0; k<i;k++){
				temp2 += x[k]*L[i][k];
			}
			x[i] = DI[i][i]*(b[i]-temp1-temp2);
		}

		count++;
		for(i=0; i<n;i++){
			double diff = fabs(x[i])-fabs(xAntes[i]);
			norma2 += diff*diff;
			xAntes[i] = x[i];
		}
		norma2 = sqrt(norma2);
		if(norma2<=tol)	break;	
	}
	
	return count;	
}

int SOR(int n, double** A, double* b, double* x, double tol, double w){
	int i,j,k,count = 0;
	double norma2;
	double** DI = mat_cria(n,n);
	double** L = mat_cria(n,n);
	double** U = mat_cria(n,n);
	double* xAntes = malloc(sizeof(double)*n);

	/*Prepara matrizes*/
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j){
				DI[i][j]=1.0/A[i][j];
				L[i][j]=0.0;
				L[i][j]=0.0;
			}else if(i>j){
				L[i][j]= A[i][j];
				U[i][j]=0.0;
				DI[i][j]=0.0;
			}else{
				U[i][j]= A[i][j];
				L[i][j]=0.0;
				DI[i][j]=0.0;
			}
		}
		xAntes[i]=x[i];
	}

	while(1){
		norma2=0.0;
		for(i=0;i<n;i++){
			double temp1=0, temp2=0;
			for(j=i+1;j<n;j++){
				temp1 += x[j]*U[i][j]; 
			}
			for(k=0; k<i;k++){
				temp2 += x[k]*L[i][k];
			}
			x[i] = DI[i][i]*(b[i]-temp1-temp2);
		}
		count++;
		for(i=0; i<n;i++){
			x[i] = ((1-w)*xAntes[i])+(w*x[i]);
			double diff = fabs(x[i])-fabs(xAntes[i]);
			norma2 += diff*diff;
			xAntes[i] = x[i];
		}
		norma2 = sqrt(norma2);
		if(norma2<=tol)	break;	
	}
	
	return count;	
}

int main (void){
	
	int n1=2, n2=6, i;
	double tol = pow(10,-7);
	double w = 1.1;
	double** A1 = mat_cria(n1,n1);
	double** A2 = mat_cria(n2,n2);

	printf("Matriz 1\n");
	A1[0][0] = 3; A1[0][1] = 1;
	A1[1][0] = 1; A1[1][1] = 2;

	double b1[] = {5, 5};
	double x1[n1];
	
	printf("	Jacobi - ");
	zeraVetor(x1,n1);
	printf("Num passos: %d\n", Jacobi(n1, A1, b1, x1, tol));
	for(i=0; i<n1; i++){
		printf("		x%d: %f\n", i, x1[i]); 
	}

	printf("\n	GS - ");
	zeraVetor(x1,n1);
	printf("Num passos: %d\n", GaussSeidel(n1, A1, b1, x1, tol));
	for(i=0; i<n1; i++){
		printf("		x%d: %f\n", i, x1[i]); 
	}

	printf("\n	SOR - ");
	zeraVetor(x1,n1);
	printf("Num passos: %d\n", SOR(n1, A1, b1, x1, tol, w));
	for(i=0; i<n1; i++){
		printf("		x%d: %f\n", i, x1[i]); 
	}

	printf("Matriz 2\n");

	A2[0][0] = 3; A2[0][1] = -1; A2[0][2] = 0; A2[0][3] = 0; A2[0][4] = 0; A2[0][5] = 0.5;
	A2[1][0] = -1; A2[1][1] = 3; A2[1][2] = -1; A2[1][3] = 0; A2[1][4] = 0.5; A2[1][5] = 0;
	A2[2][0] = 0; A2[2][1] = -1; A2[2][2] = 3; A2[2][3] = -1; A2[2][4] = 0; A2[2][5] = 0;
	A2[3][0] = 0; A2[3][1] = 0; A2[3][2] = -1; A2[3][3] = 3; A2[3][4] = -1; A2[3][5] = 0;
	A2[4][0] = 0; A2[4][1] = 0.5; A2[4][2] = 0; A2[4][3] = -1; A2[4][4] = 3; A2[4][5] = -1;
	A2[5][0] = 0.5; A2[5][1] = 0; A2[5][2] = 0; A2[5][3] = 0; A2[5][4] = -1; A2[5][5] = 3;

	double b2[] = { 2.5, 1.5, 1, 1, 1.5, 2.5};
	double x2[n2];

	printf("	Jacobi - ");
	zeraVetor(x2,n2);
	printf("Num passos: %d\n",Jacobi(n2, A2, b2, x2, tol));
		for(i=0; i<n2; i++){
		printf("	x%d: %f\n", i, x2[i]); 
	}

	printf("\n	GS - ");
	zeraVetor(x2,n2);
	printf("Num passos: %d\n",GaussSeidel(n2, A2, b2, x2, tol));
		for(i=0; i<n2; i++){
		printf("	x%d: %f\n", i, x2[i]); 
	}

	printf("\n	SOR - ");
	zeraVetor(x2,n2);
	printf("Num passos: %d\n",SOR(n2, A2, b2, x2, tol,w));
		for(i=0; i<n2; i++){
		printf("	x%d: %f\n", i, x2[i]); 
	}
	return 42;
}
