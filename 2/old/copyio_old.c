#include <stdio.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0

typedef int bool;
bool firstSpace = TRUE;
char c;

int main() {
	while (TRUE) {
		c = getchar();

		// 4 Cases:
		// CASE 1 - c is any space and there's none before it -> print space, set firstSpace to FALSE
		// CASE 2 - c is any space and there was one before -> print nothing
		// CASE 3 - c is no space -> print c, set firstSpace to TRUE if it was false
		// CASE 4 - c is EOF -> break out of the loop

		if (isspace(c) && c != '\n' ) {
			// CASE 1				 CASE 2
			if (firstSpace) c = ' '; else continue;
			firstSpace = FALSE;
		// CASE 3
		} else if (!firstSpace) 
			firstSpace = TRUE;
		// CASE 4
		else if (c == EOF) break;

		putchar(c);

		return;
	}
}
