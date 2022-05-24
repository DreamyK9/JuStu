#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int i;

	srand(time(NULL));
	printf("5 random floats (doubles) between 0 and 1:\n");

	for (i=0; i<5; i++) {
		printf("  %f", ((double) rand() /RAND_MAX));
	}

	return 0;
}
