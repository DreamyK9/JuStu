// Imperative Programmierung - Aufgabenserie 1
#include <stdio.h>
#include <string.h>

// Aufgabe 1
void main() {
	int decimal, remainder;

	// Get decimal number from user
	scanf("%d", &decimal);
	printf("Decimal: %d\n", decimal);

	// If decimal number is zero, print zero
	if (decimal == 0) printf("0");
	
	// Convert decimal number to binary
	while (decimal != 0) {
		remainder = decimal % 2;
		decimal = decimal / 2;
		printf("%d", remainder);
	}
	// Print binary number back to user
}
