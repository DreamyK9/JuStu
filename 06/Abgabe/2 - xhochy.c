#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int isnum(char str[]);

int add(int x, int y);
int mlt(int x, int y);
int pwr(int x, int y);

int main(int argc, char *argv[]) {
	/* INPUT HANDLING */ {
		for (int i=0; i<argc; i++) {
			if (strcmp("--help", argv[i]) == 0) {
				printf("Usage: %s <base> <power>\n\n", argv[0]);
				puts("This script gives back the y'th power of x,");
				puts("where x is the first argument (base) and y the second argument (power)\n");
				printf("EXAMPLE: %s 2 4 => 32\n", argv[0]);
				return 0;
			}
		}
		if (argc == 1) {
			printf("Usage: %s <base> <power>\nuse --help for more detailed information", argv[0]);
		} else if (argc < 3) {
	    	puts("ERROR: Too few arguments!\n");
		    printf("Usage: %s <base> <power>\nuse --help for more detailed information", argv[0]);
		    return 1;
		} else if (argc > 3) {
			puts("ERROR: Too many arguments!");
			printf("Usage: %s <base> <power>\nuse --help for more detailed information", argv[0]);
		}
		else if (!isnum(argv[1])) {
			puts("ERROR: The base value must be an integer number!");
			return 1;
		} else if (!isnum(argv[2])) {
			puts("ERROR: The power value must be an integer number!");
			return 1;
		}
	} /* INPUT HANDLING END */

	int base, power, result;
	base = atoi(argv[1]);
	power = atoi(argv[2]);

	result = pwr(base, power);
	printf("%d", result);
	return 0;
}

int isnum(char str[]) {
	if (!str) return 0;

	for (int i=0; str[i]; i++) {
		if (!isdigit(str[i])) return 0;
	}
	return 1;
}


/* ARITHMETIC FUNCTIONS */
int add(int x, int y) {
	for (int i=0; i<y; i++) x++;
	return x;
}

int mlt(int x, int y) {
	int x_start = x;
	for (int i=0; i<y-1; i++) x = add(x, x_start);
	return x;
}

int pwr(int x, int y) {
	int x_start = x;
	for (int i=0; i<y-1; i++) x = mlt(x, x_start);
	return x;
}
