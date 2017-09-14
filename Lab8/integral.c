#include <math.h>
#include <stdio.h> 

double f0(double x){
	return 1.0/(1.0+x);
}

double f1(double x){
	return x/sqrt((x*x)+9);
}

double f2(double x){
	return x*x*log(x);
}

double f3(double x){
	return x*x*sin(x);
}


double simpson(int m, double a, double b, double (*f)  (double x)){
	double h = (b-a)/(2.0*m);
	double fa = f(a);
	double fb = f(b);
	double fx2i_1 = 0.0;
	double fx2i = 0.0;
	int i;

	for(i=1;i<=m;i++){
		
		fx2i_1+= f(a+(h*((2*i)-1)));
		if(i!=m){
			fx2i+=f(a+(h*(2*i)));
		}
	}	

	return (h/3.0)*(fa+fb+(4*fx2i_1)+(2*fx2i));	
}

double pontoMedio(int m, double a, double b, double (*f)  (double x)){
	double h = (b-a)/m*1.0;
	double sum = 0.0;
	double w;
	int i;

	for(i=1;i<=m;i++){
		w=((a+(h*i))+(a+(h*(i-1))))/2.0;
		sum+=f(w);
	}
	return h*sum;
}

int main (void){
	
	printf("FUNCAO 1\n");
	double s161 = simpson(16, 0, 4, f1);
	printf("	s16: %.16e\n", s161);
	double s321 = simpson(32, 0, 4, f1);
	printf("	s32: %.16e\n", s321);
	double m161 = pontoMedio(16, 0, 4, f1);
	printf("	m16: %.16e\n", m161);
	double m321 = pontoMedio(32, 0, 4, f1);
	printf("	m32: %.16e\n", m321);
	printf("END FUNCAO 1\n\n");

	printf("FUNCAO 2\n");
	double s162 = simpson(16, 1, 3, f2);
	printf("	s16: %.16e\n", s162);
	double s322 = simpson(32, 1, 3, f2);
	printf("	s32: %.16e\n", s322);
	double m162 = pontoMedio(16, 1, 3, f2);
	printf("	m16: %.16e\n", m162);
	double m322 = pontoMedio(32, 1, 3, f2);
	printf("	m32: %.16e\n", m322);
	printf("END FUNCAO 2\n\n");

	printf("FUNCAO 3\n");
	double s163 = simpson(16, 0, M_PI, f3);
	printf("	s16: %.16e\n", s163);
	double s323 = simpson(32, 0, M_PI, f3);
	printf("	s32: %.16e\n", s323);
	double m163 = pontoMedio(16, 0, M_PI, f3);
	printf("	m16: %.16e\n", m163);
	double m323 = pontoMedio(32, 0, M_PI, f3);
	printf("	m32: %.16e\n", m323);
	printf("END FUNCAO 3\n\n");
	

	return 42;
}
