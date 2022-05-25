#include <stdio.h>

int main ()
{
	char c;
	// line index, len of line, index of longest line, len of longest line
	int line=1, len=0, lline=0, llen=0;

	// STEP 1: Find longest line in stdin
	while ((c = getchar()) != EOF) {
		len++;

		// On End Of Line
		if (c == '\n') {
			line++;
			// If current line was longest yet
			if (len>llen) {
				// save position and len of current line
				lline = line;
				llen = len;
			}
			len = 0;
		}
	}
	rewind(stdin);

		// STEP 2: Skip to longest line
		for (line = 1; line<lline; line++) {
			// Skip to next line
			while ((c = getchar()) != '\n');
		}

	// STEP 3: Print out longest line
	while ((c = getchar()) != '\n' && c != EOF) {
		putchar(c);
	}

	return 0;
}
