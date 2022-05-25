#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int i;

	srand(time(0));
	puts("5 random floats (doubles) between 0 and 1: ");

	for (i=0; i<5; i++) {
		printf("  %.3f", ((double) rand() /RAND_MAX));
	}
	putchar('\n');

	return 1;
}
