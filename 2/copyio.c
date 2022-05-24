#include <stdio.h>

int main() {
	// Goes through stdin till EOF is reached
	for (char c=getchar(); c != EOF; c=getchar()) {
		
		// if c is a tab or space
		if (c == '	' || c == ' ') {
			// output space
			putchar(' ');
			//skip all succeeding spaces and tabs
			for (c=getchar(); c == '	' || c == ' '; c=getchar());
		}
		// if c is no space or tab output c
		putchar(c);
	}

	return 0;
}
