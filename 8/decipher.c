#include <stdio.h>
#include <math.h>
#define N 26

char cipher(char c, int shift);
void ciphers(char *string, int shift);
int decipher(char *string);

char *help_msg = "\
%s tries to decipher a ciphered text read as argument\n\n\
Usage: %s [OPTIONS] text\n\n\
Where text is a ciphered string of characters to decipher\n\n\
Options:\n\
    -l  convert all capital letters to lower case\n\
    -h  show this help message\n\
";

const double english_freq[N] = {
8.2 , 1.5 , 2.8 , 4.3 , 12.7 , 2.2 , 2.0 ,
6.1 , 7.0 , 0.2 , 0.8 , 4.0 , 2.4 , 6.7 ,
7.5 , 1.9 , 0.1 , 6.0 , 6.3 , 9.1 , 2.8 ,
1.0 , 2.4 , 0.2 , 2.0 , 0.1
};

int lower = 0;

int main(int argc, char *argv[])
{
    /* Processing Arguments */
    //////////////////////////
    for (int i=1; i<argc; i++)
    {
        if (argv[i][0] == '-')
            switch (argv[i][1])
            {
                // convert all to lower case
                case 'l':
                    lower = 1;
                break;
                // print help message
                case 'h':
                    printf(help_msg, argv[0], argv[0]);
                    return 0;
                break;
                /////
                default:
                    printf("ERROR: There's no option '%s'\n", argv[i]);
                    printf("Use '%s -h' for detailed help\n", argv[0]);
                    return 1;
            }
    }


    char *string = argv[argc-1];
    int shift = decipher(string);

    printf("\"%s\" %d", string, shift);
    return 0;
}


int decipher(char *string)
{
    // Count Letter Occurences
    double letter_freq[N] = {0};
    double all_letter_count=0;
    char c;
    
    for(int i=0; string[i]; i++)
    {
        c = string[i];

        if (c >= 'A' && c <= 'Z') 
            c += 'a' - 'A';
            
        if (c >= 'a' && c <= 'z')
        {
            letter_freq[c - 'a']++;
            all_letter_count++;
        }
    }

    /* Calculating Ratios */
    ////////////////////////
    all_letter_count /= 100;

    for (int i=0; i<26; i++)
        letter_freq[i] /= all_letter_count;


    /* Match with English and find best matching shift */
    /////////////////////////////////////////////////////
    double match_rate = 0.0, best_rate = HUGE_VAL;
    int best_shift = 0;

    for (int shift=0; shift<26; shift++)
    {
        match_rate = 0.0;
        for (int i=0; i<26; i++)
        {
            match_rate += pow(letter_freq[(i + shift) %26] - english_freq[i], 2) / english_freq[i];
        }
        if (match_rate < best_rate) {
            best_rate = match_rate;
            best_shift = shift;
        }
    }

    // Output
    ciphers(string, -best_shift);
    return best_shift;
}


void ciphers(char* string, int shift)
{
    for (int i = 0; string[i]; i++)
    {
        string[i] = cipher(string[i], shift);
    }
}


char cipher(char c, int shift)
{
    int low = (c >= 'a' && c <= 'z');
    int capital = (c >= 'A' && c <= 'Z');
    
    // ignore capital
    if (low == capital) return c;
    // handle negative shift
    if (shift < 0) shift = 26 + shift%26;
    // lower capital letters if -l
    if (lower && capital)
    {
        c += 'a' - 'A';
        low = 1;
    }

    if (low)
        c = (c - 'a' + shift)%26 + 'a';
    else
        c = (c - 'A' + shift)%26 + 'A';

    return c;
}
