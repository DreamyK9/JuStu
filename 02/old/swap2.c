#include <stdio.h>
#define TRUE 1

char c;
int lines = 1; 

void next_line() {
	while (c != '\n') {
		c = getchar();
	}
}

void main() {
	while (c != EOF)
		c = getchar();
		if (c == '\n') lines++;

	printf("%d", lines);
	// For every line in the output
	for (int pos=0;;pos++) {
		// Get the char at position pos of the current line
		for (int i=0; i<=pos;i++) {
			c = getchar();
		}
		putchar(c);
		next_line();

		if (c == EOF)
			rewind(stdin);
	}
}
