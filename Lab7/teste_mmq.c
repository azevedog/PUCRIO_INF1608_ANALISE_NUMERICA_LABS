#include <stdio.h>
#include<stdlib.h>
#include "matriz.h"
#include "mmq.h"
#include <math.h>


void test_print(int m, int n, double** A){
	int i, j;
	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			printf("%.5g ", A[i][j]);
			//printf("linha: %d, coluna: %d valor: %g\n", i, j, A[i][j] );
		}
		printf("\n");
	}
}

void test_printv(int m, double* w){
	int i;
	for(i=0; i<m; i++){
		printf("linha: %d, valor: %.5g\n", i, w[i]);
		
	}
}

void printTiCi(double a, double b){
	float i;
	printf("PONTOS (Ti, Ci):\n");
	for(i=0.0;i<16.10;i+=0.1){
		printf("(%.2f, %g)\n", i, a*i*exp(b*i));
		//printf("%.2f\n", i);
		//printf("%g\n", a*i*exp(b*i));
	}
}

int main(void){
	int m=4, n=3;
	double** A = mat_cria(m,n);
	A[0][0]= 1.0; A[0][1]= 1.0; A[0][2]= 0.0;
	A[1][0]= 0.0; A[1][1]= 1.0; A[1][2]= 1.0;
	A[2][0]= 1.0; A[2][1]= 2.0; A[2][2]= 1.0;
	A[3][0]= 1.0; A[3][1]= 0.0; A[3][2]= 1.0;
	
	double b[m];
	b[0]= 2.0;
	b[1]= 2.0;
	b[2]= 3.0;
	b[3]= 4.0;

	double* x =mmq(m, n, A, b);
	printf("Questao 3:\n");
	printf("Vetor XBarra:\n");
	test_printv(n, x);
	printf("\n");

	double erro = norma2(m, n, A, b, x);
	printf("Erro associado: %.16g", erro);	
	printf("\n\n");

	mat_libera(m, A);
	free(x);

	printf("Questao 4:\n");
	printf("Ln(a)+bT=ln(C)-ln(T)\n");
	printf("K+bT=R\n");

	m=8;
	n=2;
	double** A2 = mat_cria(m,n);
	A2[0][0]= 1.0; A2[0][1]= 1.0;
	A2[1][0]= 1.0; A2[1][1]= 2.0;
	A2[2][0]= 1.0; A2[2][1]= 3.0;
	A2[3][0]= 1.0; A2[3][1]= 4.0;
	A2[4][0]= 1.0; A2[4][1]= 5.0;
	A2[5][0]= 1.0; A2[5][1]= 6.0;
	A2[6][0]= 1.0; A2[6][1]= 7.0;
	A2[7][0]= 1.0; A2[7][1]= 8.0;
	
	double b2[m];
	b2[0]= log(8.00)-log(1.0);
	b2[1]= log(12.3)-log(2.0);
	b2[2]= log(15.5)-log(3.0);
	b2[3]= log(16.8)-log(4.0);
	b2[4]= log(17.1)-log(5.0);
	b2[5]= log(15.8)-log(6.0);
	b2[6]= log(15.2)-log(7.0);
	b2[7]= log(14.0)-log(8.0);


	double* x2 =mmq(m, n, A2, b2);
	printf("Vetor XBarra para k e b:\n");
	test_printv(n, x2);
	printf("\n");

	double erro2 = norma2(m, n, A2, b2, x2);
	printf("Erro associado: %.16g", erro2);	
	printf("\n\n");

	printTiCi(exp(x2[0]),x2[1]);

	printf("\n\n");

	mat_libera(m, A2);
	free(x2);
	
	return 42;
} 
