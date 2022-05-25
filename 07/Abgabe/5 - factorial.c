#include <stdio.h>
#define DIGITS 32768 // maximale Länge der Output-Zahl

unsigned long long int integer(int n);
void array(int n, int *out);


int main(int argc, char *argv[]) {
	int n=0, i=0, start=0, val[DIGITS] = {0};
	char c;

	// Input
	printf("Ich berechne n! (die n-te Fakultaet)\nEingabe: n=");
	scanf("%d", &n);
	putchar('\n');

	// Berechnung
	array(n, val);

	// Output

	for (i=0; i<DIGITS; i++) {
		if (val[i] != 0) {
			start = i;
			break;
		}
	}

	printf("Die Fakultaet von %d ist:\n", n);
	for (i=start; i<DIGITS; i++) {
		printf("%d", val[i]);
	}

	return 0;
}


unsigned long long int integer(int n) {
	unsigned long long int val = 1;
	// 66! ist das Limit für jegliche Integer-Variablen
	// Werte darüber geben 0 zurück
	for (int i=2; i<n; i++) val *= i;
	return val;
}

void array(int n, int *out) {
	int i, j, buffer;

	out[DIGITS-1] = 1;


	for (i=2; i<=n; i++) {
		for (j=0; j<DIGITS; j++) {
			out[j] *= i;
		}
		for (j=DIGITS-1; j>=0; j--) {
			// Wenn out[j] mehrstellig
			buffer = out[j] - out[j]%10;
			// entferne alle außer letzter Stellen
			out[j] -= buffer;
			// und füge sie zu nächst höhererem Feld des Arrays hinzu
			out[j-1] += buffer/10;
		}
	}
}
