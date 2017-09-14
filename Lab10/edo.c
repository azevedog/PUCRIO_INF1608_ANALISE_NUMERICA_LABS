#include <stdio.h>
#include <math.h> 

static double ayTabelado[7] = {0.0, 18.0, 32.0, 45.0, 67.0, 97.0, 117.0};

double fGabaritoQ2(double t){
	return exp((t*t)/2.0)-(t*t)-2.0;
}

double ftQ2(double t, double y){
	return (t*y)+(t*t*t);
}

double RungeKutta(double t0, double t1, double h, double y0, double (*f) (double t, double y)){

	double s1=0.0, s2=0.0, s3=0.0, s4=0.0;
	while(t0 < t1){
		s1 = h*f(t0, y0);
		double t = (t0+(h/2.0));
		s2= h*f(t, (y0+(s1/2.0)));
		s3= h*f(t, (y0+(s2/2.0)));
		s4= h*f(t0+h, (y0+ s3));
		y0 = y0 + ((s1+(2.0*s2)+(2.0*s3)+s4)/6.0);
		t0+=h;
	}
	
	return y0;	
}

double TimeToY1(double t0, double y0, double y1, double h, double (*f) (double t, double y)){
	
	double s1=0.0, s2=0.0, s3=0.0, s4=0.0;
	double oldY;

	while(y0 < y1){
		oldY = y0;
		s1 = h*f(t0, y0);
		double t = (t0+(h/2.0));
		s2= h*f(t, (y0+(s1/2.0)));
		s3= h*f(t, (y0+(s2/2.0)));
		s4= h*f(t0+h, (y0+ s3));
		y0 = y0 + ((s1+(2.0*s2)+(2.0*s3)+s4)/6.0);
		t0+=h;
	}

	if(y0==y1){
		return t0;
	}else{
		return (((y1-oldY)*(t0-(t0-h)))/(y0-oldY))+(t0-h);
	}
	
}

void questao2(double gaba, double tgaba){
	
	int i;
	double h=0.1;
	
	printf("QUESTAO 2 \n");
	
	for (i=0; i<4; i++){
		double resp = RungeKutta(0.0, tgaba, h, -1.0, ftQ2);

		printf("	h=%f - Calc: %f - Esperado: %f - ErroRelativo: %f \n", h, resp, gaba, fabs((resp-gaba)/gaba)*100);
		h=h/10.0;
	}
}

void questao3a(double gaba, double tgaba){
	int i;
	double h=0.1;
	
	printf("QUESTAO 3a \n");
	for (i=0; i<4; i++){
		double resp = TimeToY1(0.0, -1.0, gaba, h, ftQ2);
		printf("	h=%f - T_Calc: %f - T_Esperado: %f - ErroRelativo: %f \n", h, resp, tgaba, fabs((resp-tgaba)/tgaba)*100);
		h=h/10.0;
	}
}

double A(double y){
	if(y<0.0 || y>6.0){
		printf("\n	y=%f, fora do intervalo tabelado\n",y);
		return 0.0;
	}

	//printf("A\n");
	int aux = y/1;
	if ((y - aux) == 0.0){
		//printf("Inteiro y=%f, aux=%d\n",y, aux);
		return ayTabelado[aux];
	}
	
	//printf("Y: %f\n",y);
	int x0 = aux;
	//printf("x0: %d\n",x0);
	int x1 = x0+1;
	if(x1>6) x1=6; //printf("x1: %d\n",x1);
	double x = y;
	double y0 =  ayTabelado[x0];// printf("y0: %f\n",y0);
	double y1 =  ayTabelado[x1];// printf("y1: %f\n",y1);
	//printf("A(y): %f\n",(((y1-y0)*(x-x0))/(x1-x0))+y0);
	return (((y1-y0)*(x-x0))/(x1-x0))+y0;
}

double ftQ3b(double t,double y){
	double d = 0.5;
	double e = 2.0;
	double g = 9.81;
	double ay = A(y);
	//printf("ftQ3b\n");
	if(ay<1.0) return -1;
	return ((M_PI*d*d)/(4.0*A(y)))*(2.0*g*sqrt(y+e));
}

double TimeToY1Decre(double t0, double y0, double y1, double h, double (*f) (double t, double y)){
	
	double s1=0.0, s2=0.0, s3=0.0, s4=0.0;
	double oldY;

	//printf("TimeToY1Decre\n");

	while(y0 > y1){
		//printf("y0: %f\n",y0);
		//printf("t0: %f\n",t0);
		s1 = h*f(t0, y0); if(s1<0.0) break;
		//printf("s1: %f\n",s1);
		double t = (t0+(h/2.0));
		s2= h*f(t, (y0-(s1/2.0))); if(s2<0.0) break;
		//printf("s2: %f\n",s2);
		s3= h*f(t, (y0-(s2/2.0))); if(s3<0.0) break;
		//printf("s3: %f\n",s3);
		s4= h*f(t0+h, (y0- s3)); if(s4<0.0) break;
		//printf("s4: %f\n",s4);
		oldY = y0;
		y0 = y0 - ((s1+(2.0*s2)+(2.0*s3)+s4)/6.0);
		t0+=h;
	}

	if(y0==y1){
		printf("y0 == y1\n");
		return t0;
	}else {
		/*printf("y0 > y1\n");
		printf("y0:%f\n",y0);
		printf("y1:%f\n",y1);
		printf("oldY:%f\n",oldY);
		printf("t0:%f\n",t0);
		printf("h:%f\n",h);*/
		return (((y1-oldY)*(t0-(t0-h)))/(oldY))+(t0-h);
	}
}

void questao3b(double valInit){
	double h = 0.1;
	int i;
	
	printf("QUESTAO 3b \n");
	for (i=0; i<4; i++){
		//printf("I=%d, h=%f\n",i,h);
		double resp = TimeToY1Decre(0.0, 6.0, valInit, h, ftQ3b);
		printf("	h=%f - T_Calc: %f\n", h, resp);
		h=h/10.0;
	}
	
}

int main (void){
	double tgaba = 2.4;
	double gaba = fGabaritoQ2(tgaba);
	
	questao2(gaba, tgaba);
	questao3a(gaba, tgaba);
	questao3b(0.0);
	return 42;
}
