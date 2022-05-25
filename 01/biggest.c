#include <stdio.h>

void main() {
	int num, biggest = 0;

	while (num >= 0) {
		scanf("%d", &num);

		switch (num > biggest) {
			case 1: biggest = num;
			break;
		}
	}
	printf("Highest Number: %d", biggest);
}
