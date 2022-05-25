#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print_file(char path[]);
int print_file_reverse(char path[]);
void print_console();
int print_console_reverse();

int main(int argc, char* argv[]) {
	unsigned char print_contents = 0, read_console = 0;

	/* INPUT HANDLING */ {
		unsigned char arg_max = 2;

		for (int i=1; i<argc; i++) {
			if (strcmp("--help", argv[i]) == 0) {
				printf("Usage: %s <file name> [-c] [-p]\n\n", argv[0]);
				puts("This script takes in a text and prints its lines out backwards\nArguments:");
				puts("  -c     read from console instead of file (uses stdin)");
				puts("  -p     print file content to console");
				return 0;
	        } else if (strcmp(argv[i], "-c") == 0) {
	        	read_console = 1; arg_max++;
			} else if (strcmp(argv[i], "-p") == 0) {
	            print_contents = 1; arg_max++;
	        }
		}
		if (argc < 2) {
			printf("Usage: %s <file name> [-c] [-p]\nuse --help for more detailed information\n", argv[0]);
		} else if (argc > arg_max) {
			puts("ERROR: Too many arguments!");
			printf("Usage: %s <file name> [-c] [-p]\nuse --help for more detailed information\n", argv[0]);
		}
    } /* INPUT HANDLING END */
		if (read_console && print_contents) {
			print_console();
			putchar('\n');
			print_console_reverse();
		} else if (read_console) {
			print_console_reverse();
		} else if (print_contents) {
			print_file(argv[1]);
			putchar('\n');
			print_file_reverse(argv[1]);
		} else {
			print_file_reverse(argv[1]);
		}
	return 0;
}

int print_file(char path[]) {
	char c;
	FILE *file = fopen(path, "r");
	if (file == 0) return 1;
	while ((c = fgetc(file)) != EOF) {
		putchar(c);
	}
	fclose(file);
	return 0;
}

int print_file_reverse(char path[]) {
	char c;
	FILE *file = fopen(path, "r");
	if (file == 0) return 1;

	for (int i=0; c != EOF; i++) {
		// set cursor at pos( next '\n')-1
		while ((c=fgetc(file)) != '\n') 
			if (c == EOF) return 0;
		fseek(file, -1, SEEK_CUR);

		// print line backwards
		while ((c = fgetc(file)) != '\n') {
			putchar(c);
			fseek(file, -2, SEEK_CUR);	
		} c = fgetc(file);
		while ((c=fgetc(file)) != '\n');
	}
	fclose(file);
	return 0;
}

void print_console() {
	char c;
	while ((c = getchar()) != EOF)
		putchar(c);
	rewind(stdin);
}

int print_console_reverse() {
	char c;
	for (int i=0; c != EOF; i++) {
		// set cursor at pos( next '\n')-1
		while ((c=getchar()) != '\n') 
			if (c == EOF) return 0;
		fseek(stdin, -1, SEEK_CUR);

		// print line backwards
		while ((c = getchar()) != '\n') {
			putchar(c);
			fseek(stdin, -2, SEEK_CUR);	
		} c = getchar();
		while ((c=getchar()) != '\n');
	}
	rewind(stdin);
	return 0;
}
