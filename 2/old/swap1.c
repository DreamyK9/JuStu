#include <stdio.h>

// Gets the length of a file
void get_length(int* add_width, int* add_height, int ll) {
 	int lines=1, chars, len=0;
 	char c;

	for (chars=1;c != EOF;chars++) {
		c = getchar();
		printf("Run %d\n", chars);
		len++;

		if (c == '\n') { 
			lines++;
			if (len < ll) ll = len;
			len = 0;
		}
	}
	
	*add_width = chars;
	*add_height = lines;
}

int tmain() {
	char c;
	int width=0, height=0, ll=0; // ll stands for longest line

	get_length(&width, &height, ll);
	rewind(stdin);
	
	for (int i=1;i<ll; i++) {
		for (int j=1;j<height;j++) {
			c = getchar();
			if (c == '\n') 
				getchar();
				break;

			putchar(c);
		}
	}
	return 0;
}

int main() {
	int width=0, height=0, maxlen=0;

	get_length(&width, &height, maxlen);
	printf("%d, %d, %d", width, height, maxlen);

	return 0;
}