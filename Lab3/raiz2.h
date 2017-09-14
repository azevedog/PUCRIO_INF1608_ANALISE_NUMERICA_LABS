#include <math.h>

int falsaposica(double a, double b, int p, double (*f) (double x), double* r);

int newtonraphson(double x0, int p, double (*f) (double x), double (*fl) (double x), double* r);

void comparaN(double a, double b, int p, int n);
