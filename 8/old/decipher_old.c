#include <math.h>
#include <stdio.h>

const double freq_eng [26] = {
8.2 , 1.5 , 2.8 , 4.3 , 12.7 , 2.2 , 2.0 ,
6.1 , 7.0 , 0.2 , 0.8 , 4.0 , 2.4 , 6.7 ,
7.5 , 1.9 , 0.1 , 6.0 , 6.3 , 9.1 , 2.8 ,
1.0 , 2.4 , 0.2 , 2.0 , 0.1
};

int best_shift;

char cipher(char c, int shift);
void decipher(char *string);

int main(int argc, char **argv) {
    char *string = argv[1];
    decipher(string);

    for (int i = 0; string[i]; i++) {
        putchar(string[i]);
    }
    printf(" %d", best_shift);
    return 0;
}

void decipher(char *string) {
    double freq_text[26] = {0};
    double match_rate, best_rate = HUGE_VAL;
    unsigned int char_count;
    int i, shift;

    // Berechnet die Häufigkeitsverteilung der Buchstaben im Text
    for (char_count=0, i=0; string[i]; i++) {
        if (string[i] >= 'a' && string[i] <= 'z') {
            freq_text[string[i] - 'a']++;
            char_count++;
        }
    }

    // Rechnet in Prozent um
    for (char_count /=100 , i=0; i<26 ;i++)
        freq_text[i] /= char_count;

    // Vergleicht Buchstaben-Verteilung mit Englisch
    for (shift=0; shift<26; shift++) {
        for (match_rate=0.0, i=0; i<26;i++)
            match_rate += pow(freq_text[(i+shift) % 26] - freq_eng[i] , 2) / freq_eng[i];

        if (match_rate < best_rate) {
            best_rate = match_rate;
            best_shift = shift;
        }
    }

    for (i=0; string[i]; i++) {
        string[i] = cipher(string[i], -best_shift);
    }
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
