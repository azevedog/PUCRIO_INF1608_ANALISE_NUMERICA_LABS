#include "gauss.h"
#include <stdio.h>
#include "matriz.h"
#include <stdlib.h>


void test_preenche(int m, int n, double** A){
	int i, j;
	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			A[i][j] = i*10.0+j;
		}
	}
}

void test_print(int m, int n, double** A){
	int i, j;
	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			//printf("%g ", A[i][j]);
			printf("linha: %d, coluna: %d valor: %g\n", i, j, A[i][j] );
		}
		printf("\n");
	}
}

void test_preenchev(int m, double* v){
	int i;
	for(i=0; i<m; i++){
		v[i]=i+1.0;
		
	}
}

void test_printv(int m, double* w){
	int i;
	for(i=0; i<m; i++){
		printf("linha: %d, valor: %g\n", i, w[i]);
		
	}
}

int main(void){
	int i=3, j=3;
	double** A = mat_cria(i,j);
	A[0][0]= 1.0; A[0][1]= 2.0; A[0][2]=-1.0;
	A[1][0]= 2.0; A[1][1]= 1.0; A[1][2]=-2.0;
	A[2][0]=-3.0; A[2][1]= 1.0; A[2][2]= 1.0;
	
	double** P1 = fatoracao(i, A);
	double v1[i];
	v1[0]= 3.0;
	v1[1]= 3.0;
	v1[2]=-6.0;	
	double* x1 = substituicao(i, A, P1, v1);
	test_printv(i, x1);
	free(A);
	free(P1);
	free(x1);

	printf("\n\n");

	i=3;
	j=3;
	double** B = mat_cria(i,j);
	B[0][0]= 2.0; B[0][1]= 1.0; B[0][2]= 5.0;
	B[1][0]= 4.0; B[1][1]= 4.0; B[1][2]=-4.0;
	B[2][0]= 1.0; B[2][1]= 3.0; B[2][2]= 1.0;

	double** P2 = fatoracao(i, B);
	double v2[i];
	v2[0]= 5.0;
	v2[1]= 0.0;
	v2[2]= 6.0;	
	double* x2 = substituicao(i, B, P2, v2);
	test_printv(i, x2);
	free(B);
	free(P2);
	free(x2);
	
	printf("\n\n");

	i=6;
	j=6;
	double** A3 = mat_cria(i,j);
	A3[0][0]= 3.0; A3[0][1]=-1.0; A3[0][2]= 0.0; A3[0][3]= 0.0; A3[0][4]= 0.0; A3[0][5]= 0.5;
	A3[1][0]=-1.0; A3[1][1]= 3.0; A3[1][2]=-1.0; A3[1][3]= 0.0; A3[1][4]= 0.5; A3[1][5]= 0.0;
	A3[2][0]= 0.0; A3[2][1]=-1.0; A3[2][2]= 3.0; A3[2][3]=-1.0; A3[2][4]= 0.0; A3[2][5]= 0.0;
	A3[3][0]= 0.0; A3[3][1]= 0.0; A3[3][2]=-1.0; A3[3][3]= 3.0; A3[3][4]=-1.0; A3[3][5]= 0.0;
	A3[4][0]= 0.0; A3[4][1]= 0.5; A3[4][2]= 0.0; A3[4][3]=-1.0; A3[4][4]= 3.0; A3[4][5]=-1.0;
	A3[5][0]= 0.5; A3[5][1]= 0.0; A3[5][2]= 0.0; A3[5][3]= 0.0; A3[5][4]=-1.0; A3[5][5]= 3.0;
	
	double** P3 = fatoracao(i, A3);
	double v3[i];
	v3[0]= 2.5;
	v3[1]= 1.5;
	v3[2]= 1.0;
	v3[3]= 1.0;
	v3[4]= 1.5;
	v3[5]= 2.5;	
	double* x3 = substituicao(i, A3, P3, v3);
	test_printv(i, x3);
	free(A3);
	free(P3);
	free(x3);

	return 42;
}

