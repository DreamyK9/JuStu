#include <stdio.h>

int main () {

	int num=0, n=2, pow=0;

	printf("Please type a number: ");
	scanf("%d", &num);

		if (num == 0) {
			printf("\n0"); return 0;
		} else if (num == 1) {
			printf("\n1"); return 0;
		} else if (num == -1) {
			printf("\n-1"); return 0;
		} else if (num > 0) {
			printf("\n1");
		} else if (num < 0) {
		 	printf("\n-1");
		 	num *= -1;
		}

	for (n=2; num>1; n++, pow=0) {
		if (num % n == 0) {
			while (num % n == 0) {
				num /= n;
				pow++;
			}
			
			if (pow > 1) {
				printf(" * %d^%d",n, pow);
			} else {
				printf(" * %d", n);
			}
		}
	}

	return 0;
}
