#include "mmq.h"
#include "matriz.h"
#include <stdlib.h> 
#include "gauss.h"
#include <math.h>

double* mmq(int m, int n, double** A, double* b){
	double** AT = mat_cria(n,m);
	mat_transposta (m,n, A,AT);
	
	double** ATA = mat_cria(n,n);
	mat_multm(n, m, n, AT, A, ATA);

	double* ATb = (double*) malloc(sizeof(double)*n);
	mat_multv(n, m, AT, b, ATb);

	double** P = fatoracao(n, ATA);

	double* x = substituicao(n, ATA, P, ATb);
	
	mat_libera(n,P);
	mat_libera(n,AT);
	mat_libera(n,ATA);
	free(ATb);

	return x;
}


double norma2(int m, int n, double** A, double* b, double* x){
	int i;	
	double erro=0.0;
	double Ax[m];
	mat_multv(m, n, A, x, Ax);

	for(i=0; i<m; i++){
		erro+=sqrt(pow(b[i]-Ax[i], 2.0));
	}

	return erro;
}
