#include <math.h>
#include <stdio.h>
#include "brent.h"

void comparaN(double a, double b, int p, int n){
	double nCalc=log2(2*(b-a)*pow(10,p))-1;
	printf("	Brent rodado com N: %d iteracoes, esperado %.4g\n", n, nCalc);
}

double dist(double a, double b){
	return a<=b? b-a: a-b;
}

double bhaskara(double a, double b, double c){
	double x1;
	double x2;
	double delta= sqrt(pow(b,2)-4.0*a*c);
	//printf("			bhaskara\n");
	x1 = (-b+delta)/2.0*a;
	//printf("			x1:%f, c:%f\n", x1, c);
	x2 = (-b-delta)/2.0*a;
	//printf("			x2:%f, c:%f\n", x2, c);
	if(dist(c,x1)<=dist(c,x2)) return x1;
	//printf("			(x2 ganhou!)\n");
	return x2;
}


double brent(double x0, double x1, int p, double (*f)  (double x)){
	double oX0 = x0;
	double oX1 = x1;
	double e=0.5*pow(10,-p);
	double fx0 = (*f)(x0);
	double fx1 = (*f)(x1);
	double xm;
	double fxm;
	double x2;
	double fx2;
	int n=0;
	printf("	BrentMethod\n");
	while(((x1-x0)/2.0)>e){

		xm = (x1+x0)/2.0;
		fxm = (*f)(xm);
		if(fxm<=e){
			break;
		}
		n++;
		//IQI
		printf("		N%d - tentando IQI\n",n);
		//x2 = bhaskara(x0, x1, xm);
		x2 = ((x0*fx1*fxm)/((fx0-fx1)*(fx0-fxm)))+((x1*fx0*fxm)/((fx1-fx0)*(fx1-fxm)))+((xm*fx0*fx1)/((fxm-fx0)*(fxm-fx1)));
		fx2 = (*f)(x2);		
		if(fabs(fx2)<fabs(fxm)){
			if(fx0*fx2<0.0){
				if(x0+x2/2.0<xm){
					x1=x2;
					fx1=fx2;
					printf("			continue\n");
					continue;
				}
			}
			else{
				if(x1+x2/2.0<xm){
					x0=x2;
					fx0=fx2;
					continue;
printf("			continue\n");
				}
			}
		
		}

		//secante
		printf("		N%d - tentando Secante\n",n);
		x2= x1-((fx1*(x1-x0))/(fx1-fx0));
		fx2 = (*f)(x2);		
		if(fabs(fx2)<fabs(fxm)){
			if(fx0*fx2<0.0){
				if(x0+x2/2.0<xm){
					x1=x2;
					fx1=fx2;
					continue;
printf("			continue\n");
				}
			}
			else{
				if(x1+x2/2.0<xm){
					x0=x2;
					fx0=fx2;
					continue;
printf("			continue\n");	
				}
			}
		
		}
	
		//Bissecao
		printf("		N%d - tentando Bissecao\n",n);
		if(fx0*fxm<0){
			x1=xm;
			x1=fxm;
			continue;
		}else{
			x0=xm;
			fx0=fxm;
			continue;
		}
	}
	comparaN(oX0, oX1, p, n);
	return xm;
}
