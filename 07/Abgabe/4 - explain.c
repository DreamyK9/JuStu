#include <stdio.h>

double fnord_rec(double v);
double fnord_loop(double v);

int main () {

	double (*fnord)(double) = &fnord_loop;

	printf("%.5lf\n", fnord(15.3));

	return 0;
}

double fnord_rec(double v) {
	int c = getchar();
	if (c >= '0' && c <= '9') return fnord_rec ( v *10+( c - '0' ));
	ungetc(c, stdin);
	return v;
}

double fnord_loop(double v) {
	int c;
	while ((c = getchar()) >= '0' && c <= '9') {
		v = 10*v + (c - '0');
	}
	ungetc(c, stdin);
	return v;
}
