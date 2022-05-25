#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* read_file(const char* file_name) {
	FILE *file = fopen(file_name, "r");
	if (file == 0) return 0;

	fseek(file, 0, SEEK_END);
	long len = ftell(file);
	char* buffer = malloc(len);
	fseek(file, 0, SEEK_SET);
	fread(buffer, len, 1, file);
	fclose(file);
	buffer[len] = 0;

	return buffer;
}

char* split_lines(char* input) {
	int line_count=0, longest_line=0, char_count=0, i=0, j=0;

	// get line count + longest line
	for (i=0; input[i]!=0; i++, char_count++) {
		if (input[i] == '\n') {
			longest_line = (char_count > longest_line) ? char_count : longest_line;
			char_count = 0;
			line_count++;
		}
	}

	char* output[line_count][longest_line];

	// split lines
	int leftover=0;
	for (i=0; input[leftover]!=0; i++) {
		for(j=0; input[j+leftover]!='\n'; j++) {
			*output[i][j] = input[j+leftover];
		}
		output[i][j] = 0;
		leftover += j;
	}

	*(output[line_count])=0;
}

int main(int argc, char *argv[]) {
	int i=0, j=0;

	if (argc < 2) {
		printf("Usage: %s <file path> [-o]\n", argv[0]);
		return 1;
	}

	unsigned char print_contents = 0;

	for (int i = 2; i < argc; i++) {
		if (strcmp(argv[i], "-o") == 0) {
			print_contents = 1;
		}
	}
	char* raw = read_file(argv[1]);
	
	if (raw == 0) {
        printf("%s: Error: File couldn't be opened", argv[0]);
        return 1;
    }

    if (print_contents) {
        printf("%s\n", raw);
    }

	char* data = split_lines(raw);

	// output in reverse
	for (i=0; data[i]!=0; i++) {
		putchar(data[i]);
		// for (j=0; data[i][j]!=data[]; j++) {
		// 	putchar(data[i][j]);
		// }
	}
}
