// 2. Präsenz
// Jonas Wolf, Lennnart Vosseler, Ivan Kuznetsov

#include <stdio.h>
#include <ctype.h>
#include <math.h>

int getlen();
void read(char *arr);
void count(int len, char *input, int *output);
void calc(int *absolut, float *prozent);

int main () {
						// 256 ascii characters + letter count
	int len = getlen(), cnt[257] = {0};
	char data[len];
	float prozent[26];

	read(data);
	count(len, data, cnt);
	calc(cnt, prozent);

	// Text Ausgabe
	puts("\n\n Letter |  Percentage");
	puts("--------|-------------");
	for(int i = 0; i < 26; i++)
		printf("    %c   |  %6.2f %%\n",i+97, prozent[i]);
	
	return 0;
}

// Get length of input file
int getlen() {
    int c, l = 0;
    while((c=getchar())!=EOF) l++;
   	
   	rewind(stdin);
    return l;
}
// Read input file
void read(char *arr) {
    char c;
    int cn = 0;

	while ((c=getchar())!=EOF) {
        if (isalpha(c)) c=tolower(c);
        arr[cn]=c;
        ++cn;
    }
}
// Count the appearence of each character
void count(int len, char *input, int *output) {

	for (int i = 0; i<len; i++) {
		// character counts
		output[input[i]]++;
		// general letter count
		if (isalpha(input[i])) output[256]++;
	}
}
// Calculate percentage values
void calc(int *absolut, float *prozent) {
	for (int i = 0; i < 26; i++)
					 // Count of current letter divided by  
		prozent[i] = (float) absolut[i+97] / absolut[256] * 100;
}
