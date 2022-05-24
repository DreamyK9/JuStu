#include <stdio.h>
#include <ctype.h>
#define ASCII 256

void count(int len, char *input, int *output) {

	for (int i = 0; i<len; i++) {
		// values 
		output[input[i]]++;
		// letter count
		output[ASCII] += isalpha(input[i]);
	}
}

int main () {
	int cnt[ASCII+1] = {0};
	char test[79] = "ein auto mit servolenkung hat ganz viele vorteile, wie z.b. schnelleres fahren!";

	count(27, test, cnt);

	for (int i=0; i<ASCII+1; i++)
		if (cnt[i] != 0) printf("%d %d\n", i, cnt[i]);

	return 0;
}
