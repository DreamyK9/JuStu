#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int max(int x, int y);
int isnum(char str[]);
int isprime(int x);

int ggT(int x, int y);

int main (int argc, char *argv[]) {
	/* INPUT HANDLING */ {
		for (int i=1; i < argc; i++) {
			if (strcmp("--help", argv[i]) == 0) {
				printf("Usage: %s <number 1> <number 2>\n\n", argv[0]);
				puts("This script calculates the smallest common divider of two numbers");
				puts("passed as command line arguments as shown above\n");
				printf("EXAMPLE: %s 14 32 => 2\n", argv[0]);
				return 0;
			}
		}
		if (argc < 2) {
			printf("Usage: %s <number 1> <number 2>\nuse --help for more detailed information\n", argv[0]);
		}
		else if (argc < 3) {
	    	puts("ERROR: Too few arguments!\n");
		    printf("Usage: %s <number 1> <number 2>\nuse --help for more detailed information\n", argv[0]);
		    return 1;
		} else if (argc > 3) {
			puts("ERROR: Too many arguments!");
			printf("Usage: %s <number 1> <number 2>\nuse --help for more detailed information\n", argv[0]);
		}
		else if (!isnum(argv[1]) || !isnum(argv[2])) {
			puts("ERROR: Both numbers must be integers!\n");
			return 1;
		}
	} /* INPUT HANDLING END */

	int x, y, result;
	x = atoi(argv[1]);
	y = atoi(argv[2]);

	// if ((x == 0) + (y == 0) == 1) {
	// 	printf("There is no smallest common divider between zero and a nonzero integer\n");
	// 	return 1;
	// }

	result = ggT(x, y);
	printf("The smallest common divider of %d and %d  is:\n %d\n", x, y, result);
	return 0;
}

int max(int x, int y) {
	return (x > y) ? x : y;
}

int isnum(char str[]) {
	if (!str) return 0;

	for (int i=0; str[i]; i++) {
		if (!isdigit(str[i])) return 0;
	}
	return 1;
}

int isprime(int x) {
	for (int i=2; i<x; i++) {
		if (x % i == 0) {
			return 0;
		}
	}
	return 1;
}

int ggT(int x, int y) {
	if (x == 0) return y;
	if (y == 0) return x;
	
	int max_ = max(x, y);
	for (int i=2; i<max_;) {
		if ((x % i == 0) && (y % i == 0)) {
			x /= i; y /= i;
		} else
		while (!isprime(i++));
	}
	return x;
}
