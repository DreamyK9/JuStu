#include <stdio.h>
#include <math.h>

int main ()
{
	char c;
	// line index, length of line
	int line=1, len=0;
	// indices of longest lines, length of longest line
	int /*llines[0],*/ llen=0;
	//number of lines with length llen, position in array
	int count=0, i=0;


	// STEP 1: Get length of longest line(s)
	c = getchar();
	do {
		len++;
		if (c == '\n' || c == EOF) {
			llen = fmax(len, llen);
			len = 0;
		}
	} while ((c = getchar()) != EOF);
	rewind(stdin);
	len = 0;
	printf("Length: %d\n", llen);


	// STEP 2: Get the number of longest lines
	c = getchar();
	do {
		len++;
		if (c == '\n' || c == EOF) {
			if (len == llen) count++;
			len++;
		}
	} while ((c = getchar()) != EOF);
	rewind(stdin);
	int llines[count];
	len = 0;
	printf("Count: %d\n", count);


	// STEP 3: Save position(s) of longest line(s)
	c = getchar();
	i = 0;
	do {
		len++;
		if (c == '\n' || c == EOF) {
			if (len == llen){
				llines[i] = line;
				i++;
			}
			line++;
		}
	} while ((c = getchar()) != EOF);
	rewind(stdin);


	// STEP 4: Print out longest line(s)
	for (i=0; i<=count; i++) {
		printf("Final Loop %d - value: %d\n", i, llines[i]);
		// 4A - Skip to current line
		for (line=1; line<llines[i]; line++) {
			while ((c = getchar()) != '\n' && c != EOF);
			//printf("Loop A ");
		}

		// 4B: Print out current line
		while ((c = getchar()) != '\n' && c != EOF) {
			printf("Loop B");
			putchar(c);
		}
		rewind(stdin);
	}

	return 0;
}
