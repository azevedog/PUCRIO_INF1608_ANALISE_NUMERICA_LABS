#include "matriz.h"
#include <stdio.h>

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
			printf("linha: %d, coluna: %d valor: %g\n", i, j, A[i][j] );
		}
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
	int m=2, n=3;
	double v[n];
	double w[m];
	
	printf("\nTeste cria Matriz\n");
	double** A = mat_cria(m,n);
	test_preenche(m,n, A);
	test_print(m,n, A);
	
	printf("\nTeste Transposta\n");
	double** T = mat_cria(n,m);
	mat_transposta(m,n, A, T);
	test_print(n,m, T);
	
	printf("\nTeste MultV\n");
	test_preenchev(n, v);
	mat_multv(m,n,A,v,w);
	test_printv(m, w);
	
	printf("\nTeste Multm\n");
	double** C = mat_cria(m,m);
	mat_multm(m,n,m,A,T,C);
	test_print(m,m, C);
	
	mat_libera(m, A);
	mat_libera(n, T);
	mat_libera(m, C);
	return 42;
}
