#include <stdio.h>
#include <ctype.h>

char c;
int line, word;

void new_word() {
	// Prints out next line and word counter in new line
	printf("\n%d.%d ", line, word);
	// skip all spaces 
	for (c=getchar(); isspace(c) || ispunct(c) || c == '\n'; c = getchar());
	putchar(c);
}

// Input oriented approach
int main() {
	// Prints out first line and word counter
	printf("\n%d.%d ", line, word);
	// Goes through stdin till EOF is reached
	for (c=getchar(); c != EOF; c=getchar()) {
		// If c is a space or tab
		if (c == ' ' || c == '	') {
			// skip to next word (in new line)
			// with higher word counter
			word++;
			new_word();
		// If c is newline
		} else if (c == '\n') {
			// skip to next word (in new line)
			// with higher line counter
			word = 1;
			line++;
			new_word();
		} else if (ispunct(c)) continue;
		  else putchar(c);
	}

	return 0;
}

// Unused output oriented approach
/*int tmain() {
	for (line=1; ;line++) {
		for (word=1; ;word++) {
			printf("\n%d.%d ", line, word);
			for (c=getchar(); c!=EOF && c!= '\n'; c=getchar(), word++) {
				if (c == ' ' || c == '\n' || c == '	') {
					for (c=getchar(); c == ' ' || c == '	' || c == '\n'; c=getchar());
					break;
				} else if (!isalnum);
			}
		}
	}
}*/