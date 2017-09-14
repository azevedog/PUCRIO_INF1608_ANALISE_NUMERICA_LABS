#include <math.h>
#include <stdio.h>

double fcos(double x);

void conta(){
	double v= 2.3-2.0-0.3;
	printf("		Resultado Conta: %.16g\n", v);
}

int main(void){
	double erro, mine, lib, diff, x=0.0;
	char* msg1="Aceito!";
	char* msg2="ERRO!";
	printf("\nINICIO\n");
	printf("	INICIO - TAYLOR\n");
	while(x<=M_PI){
		mine = fcos(x);
		lib = cos(x);
		erro = x-M_PI/2;
		erro = erro<0?erro*-1.0:erro;
		erro=erro*erro*erro*erro*erro;
		erro=erro/120;
		diff = mine - lib;
		diff=diff<0?diff*-1.0:diff;
		if (diff<=erro){
			printf("		X: %.16g - Taylor: %.16g - MATH.H: %.16g - DIFF: %.16g - Erro: %.16g - Resultado: %s\n", x, mine, lib, diff, erro, msg1);
		}else{
			printf("		X: %.16g - Taylor: %.16g - MATH.H: %.16g - DIFF: %.16g - Erro: %.16g - Resultado: %s\n", x, mine, lib, diff, erro, msg2);
		}
		x+=M_PI/4.0;
	}
	printf("	FIM - TAYLOR\n");
	printf("\n	INICIO - CONTA\n");
	conta();
	printf("	FIM - CONTA\n");
	printf("FIM\n\n");
	return 42;
}