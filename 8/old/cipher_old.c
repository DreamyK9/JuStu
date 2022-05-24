#include <stdio.h>

char cipher(char c, int shift);
// char cipher_old(char c, int shift);
// char cipher_old2(char c, int shift);

int lower = 0;

int main(int argc,char *argv[]) {
    for (int i=0; i<argc; i++) {
        if (argv[i] == "-l")
            lower = 1; 
    }

    char *string = argv[argc-2];
    char *number = argv[argc-1];
    
    int negative = 0;
    int shift = 0;
    for (int i = 0; number[i]; i++) {
        if (number[i] == '-') negative = 1;
        ////
        else shift = 10*shift + (number[i] - '0');
	}
    if (negative) shift *= -1;

    for (int i = 0; string[i]; i++) {
        if (string[i] >= 'a' && string[i] <= 'z' || string[i] >= 'A' && string[i] <= 'Z') {
            putchar(cipher(string[i], shift));
        } else {
            putchar(string[i]);
        }
    }

    return 0;
}

char cipher_old2(char c, int shift) {
    int low = (c >= 'a' && c <= 'z');
    int capital = (c >= 'A' && c <= 'Z');
    if (lower && capital) c += 32;

    //  return error when c is not a letter
    if (low == capital) return 0;

    c += shift % 26;

    if (low) {
        if (c < 'a') {
            c = 'z' + c-'z';
        } else
        if (c > 'z') {
            c = 'a' + c-'a';
        }
    } else
    if (capital) {
        if (c < 'A') {
            c = 'Z' + c-'Z';
        } else
        if (c > 'Z') {
            c = 'A' + c-'A';
        }
    }
}

char cipher_old(char c, int shift) {
    int low = (c >= 'a' && c <= 'z');
    int capital = (c >= 'A' && c <= 'Z');
    
    //  return error when c is not a letter
    if (low == capital) return 0;

    if (shift > 0) {
        for (int i = 0; i < shift; i++) {
            if (c > 'z' && low) {
                c = 'a';
            } else if (c > 'Z' && capital) {
                c = 'A';
            } 
            c++;
        }
    } else if (shift < 0) {
        for (int i = 0; i > shift; i--) {
            if (c < 'a' && low) {
                c = 'z';
            } else if (c < 'A' && capital) {
                c = 'Z';
            }
            c--;
        }
    }
    return c;
}

char cipher(char c, int shift) {
    int low = (c >= 'a' && c <= 'z');
    int capital = (c >= 'A' && c <= 'Z');
    if (low == capital) return 0;

    if (low) {
        c = (c - 'a' + shift)%26 + 'a';
    } else {
        c = (c - 'A' + shift)%26 + 'A';
    }
    
    return c;
}
