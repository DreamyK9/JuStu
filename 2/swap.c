#include <stdio.h>

// Gets number of lines and length of longest line from stdin
void getsize(int* add_lines, int* add_len) {
	int line=0, maxlen=0, len=0;
	
	// Goes through stdin char by char
	for (char c=getchar(); /*Infinity*/; c=getchar(), len++) {
		// If the cursor reaches EOF or newline respectively
		// -> line and maxlen are updated
		if (c == '\n' || c == EOF) {
			line++;
			maxlen = (len > maxlen ? len : maxlen);
			len = 0;
		}
		if (c == EOF) break;
	}

	// Output the values
	*add_lines = line;
	// Decreasing maxlen by 1 as it contains the newline character
	*add_len = maxlen -1;
	rewind(stdin);
}

// Gets char at specified position
// l = line; c = char;
char getcharat(int l, int c) {
	// line, char
	char ch;

	// Skips to line l
	for (int i=0; i<l; i++) {
		// Skips to next line every time called
		for (ch=getchar(); ch != '\n'; ch=getchar())
			// Return '/' if line index exceeds EOF
			if (ch == EOF) { 
				rewind(stdin);
				return '/';
			}
	}

	// Skips to char c-1 in line l
	for (int i=0; i<=c; i++) {
		ch = getchar();
		// Returns '.' if char index exceeds the lenght of line l
		if (ch == '\n' || ch == EOF) {
			rewind(stdin);
			return '.';
		}
	}

	// Return char at position c (ch)
	rewind(stdin);
	return ch;
}


int main() {
	// Gets dimensions of stdins content
	int width=0, height=0;
	getsize(&width, &height);

	// Prints it out to the screen reformated
	for (int y=0; y<height; y++) {
		for (int x=0; x<width; x++) 
			putchar(getcharat(x, y));
		putchar('\n');
	}

	return 0;
}

// Unused alternative approach
/*
int old_main() {
	int width=0, height=0;

	getlen(&width, &height);
	printf("%d, %d\n\n", width, height);

	for (int y=1; y<=height; y++) {
		for (int x=1; x<=width; x++) {
			putchar(getcharat(x, y));
		}
		putchar('\n');
	}
	
	return 0;
}*/
