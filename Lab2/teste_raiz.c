#include "raiz.h"
#include <stdio.h>
#include <math.h>

double reta(double x){
	return -1.0+x;
}


double funcDeTeste2(double x){
	return -2.5/(-x+1.8);
}

double funcDeTeste(double x){
	return sin(x)-pow(x,3);
}

double funcParaquedista(double x){
	return ((9.8*x*(1-exp((-15*9)/x)))/15)-35;
}

int main(void){
	
	printf("INICIO\n");
	//double resp = bissecao (0.0, 5, 6, reta);
	double resp = bissecao (0.5, 1.5, 6, funcDeTeste);
	printf("	A raiz pelo método da bissecao eh: %.16g\n", resp);
	double resp1 = bissecao (58, 61, 6, funcParaquedista);
	printf("	A MASSA pelo método da bissecao eh: %.16g\n", resp1);
	double resp2 = pontofixo (5, .0005, funcDeTeste2);
	printf("	A raiz pelo método do ponto fixo eh: %.16g\n", resp2);
	printf("FIM\n");
	
}