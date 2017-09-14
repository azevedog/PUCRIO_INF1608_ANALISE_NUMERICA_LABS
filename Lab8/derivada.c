#include <math.h>
#include <stdio.h> 

double static E_MAQ = 1.110223025E-16;

double calcErroTeorico(double h){
	return ((h*h*(-0.0625))+(E_MAQ/h));
}

int main (void){

	double valorAnalitico = -1.0/4.0;
	double i;
	double valorCalculado;
	double h;
	double erroTeorico;
	double erroNumerico;
	double minErroTeorico=HUGE_VAL;
	double minErroNumerico=HUGE_VAL;
	double minHTeorico=0.0;
	double minHNumerico=0.0;

	printf("\n");

	for(i=-1.0;i>-13.0;i--){
		h = pow(10.0,i);
		erroTeorico = calcErroTeorico(h);
		valorCalculado = ((1.0/(2.0+h)) - (1.0/(2.0-h)))/(2*h);
		
		

		printf("%.2e  ",h);
		printf("%.16e  ",valorCalculado);
		printf("%.2e  ",valorAnalitico);

		erroNumerico =valorCalculado-valorAnalitico;

		printf("%.16e  ",erroNumerico);
		printf("%.16e\n",erroTeorico);

		erroTeorico = fabs(erroTeorico);
		if(erroTeorico<minErroTeorico){
			minErroTeorico = erroTeorico;
			minHTeorico = h;
		}
		erroNumerico = fabs(erroNumerico);
		if(erroNumerico<minErroNumerico){
			minErroNumerico = erroNumerico;
			minHNumerico = h;
		}

	}

	printf("\n");
	printf("O H que gerou o menor erro numerico foi:%.2e\n", minHNumerico);	
	printf("O H que gerou o menor erro teorico foi: %.2e\n", minHTeorico);	

	if(minHTeorico==minHNumerico){
		printf("Os H's de menor erro sao compativeis!\n");
	}else{
		printf("Os H's de menor erro NAO sao compativeis!\n");
	}

	printf("\n");
	
	return 42;
}
