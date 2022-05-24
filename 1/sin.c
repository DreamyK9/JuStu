#include <stdio.h>
#include <math.h>

long long fac(int x)
{
	int i;
	long long y = 1;

	for (i=1;i<=x;i++)
		y = y * i;

	return y;
}

double sin(double x)
{
	// In Bogenmaß umrechnen
	x = x * M_PI/180;

	int n;
	double sine = 0;
	for (n=0; n<8; n++)
		sine += pow(-1, n) * pow(x, 2*n+1) / fac(2*n + 1);
	return sine;
}

int main()
{
	// Print table head
	printf("Grad | Sinus\n");

	// Table body
	for (int x=0; x<=720; x+=15) {
		/* Calculate the sine of x */
		printf("%3d   %lf \n",x ,sin(x % 360));
	}
	return 0;
}