#include <stdlib.h>
#include <stdio.h>

char cipher(char c, int shift);
void ciphers(char *string, int shift);

char *help_msg = "\
Usage: %s [OPTIONS] text shift\n\n\
Where text is a string of characters to convert\n\
and shift is the character shift to be applied to the string\n\n\
Options:\n\
    -l  convert all capital letters to lower case\n\
    -h  show this help message\n\
";

int lower = 0;

int main(int argc,char *argv[])
{
    /* Argument Processing */
    /////////////////////////
    for (int i=1; i<argc-1; i++)
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
                    printf(help_msg, argv[0]);
                    return 0;
                break;
                /////
                default:
                    printf("ERROR: There's no option '%s'\n", argv[i]);
                    printf("Use '%s -h' for detailed help\n", argv[0]);
                    return 1;
            }
    }


    /* Accessing Input */
    /////////////////////
    char *string = argv[argc-2];
    char *number = argv[argc-1];
    

    /* Converting Shift Input to integer */
    ///////////////////////////////////////
    int negative = 0;
    int shift = 0;

    for (int i = 0; number[i]; i++)
    {
        if (number[i] == '-') negative = 1;
        ////
        else shift = 10*shift + (number[i] - '0');
	}
    if (negative) shift *= -1;


    /* Ciphering and Output of results */
    /////////////////////////////////////
    ciphers(string, shift);
    printf("\"%s\"", string);
    return 0;
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
