#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define STD_OUTPATH "./shuffle.txt"
#define DEFAULT_ITERATIONS 1000
/* ----------------------------- Data Structures ---------------------------- */
struct args {
    char *output_path;
    int n;
    int iterations;
    bool print_table;
    /////////////////
    bool print_console;
    bool help_printed;
    bool error;
};
/* ---------------------------- Utility Function ---------------------------- */
// swap values of two vars
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
// fill array of len n with numbers 0-n in order
void fill(int arr[], int len)
{
    for (int i = 0; i < len; i++)
        arr[i] = i;
}
void fill_with(int arr[], int len, int value)
{
    for (int i = 0; i < len; i++)
    arr[i] = value;
}
// shuffle an array
void shuffle(int arr[], int n)
{
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i=n-1; i > 0; i--)
    {
        // picks a random index between 0 and i
        int j = rand() % (i+1);

        // swaps arr[i] with element at random index
        swap(&arr[i], &arr[j]);
    }
}
// check if an array is in order
bool inorder(int arr[], int len)
{
    for (int i=0; i < len; i++)
        if (arr[i] != i)
            return false;

    return true;
}
int average(int arr[], int len)
{
    unsigned long long sum = 0;
    for (int i=0; i < len; i++)
        sum += arr[i];
    
    return (int)sum/len;
}
void hidecursor(void)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}
/* --------------------------- Procedure Funtions --------------------------- */
struct args parse_args(int argc, char **argv)
{
    const char* const help_msg =
"\n\
Usage: %s [OPTIONS] N\n\
\n\
calculates average number of random shuffles\n\
to get a set of N cards in order\n\
\n\
Required Arguments:\n\
    N           number of cards\n\
\n\
Optional Arguments:\n\
    -c          outputs to console (stdout) instead of output file,\n\
          overwrites -o\n\
    -h          shows this help message and exits\n\
    -i          specifies number of iterations for each average, defaults to %d\n\
    -o          specifies path of output file, defaults to \"%s\"\
    -t          table mode: print table with output for all numbers 0-N\n\
\n\
NOTE:\n\
    currently only table mode works and will always be active\n\
";

    struct args data = {STD_OUTPATH, 0, DEFAULT_ITERATIONS, false, false, false, false};
    bool value_demanded = false;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (value_demanded)
            {
                printf("ERROR: Missing value for %s\n", argv[i-1]);
                data.error = true;
                return data;
            }
            switch(argv[i][1])
            {
                case 'c':
                    data.print_console = true;
                break;
                case 'h':
                    printf(help_msg, argv[0], DEFAULT_ITERATIONS, STD_OUTPATH);
                    data.help_printed = true;
                return data;
                case 'i':
                    data.iterations = atoi(argv[i+1]);
                    value_demanded = true;
                break;
                case 'o':
                    data.output_path = argv[i+1];
                    value_demanded = true;
                break;
                case 't':
                    data.print_table = true;
                break;
                default:
                    printf("ERROR: There's no option '%s'\n", argv[i]);
                    data.error = true;
                return data;
            }
        } else
        if (value_demanded)
            value_demanded = false;
        else
            data.n = atoi(argv[i]);
    }

    if (!data.n)
    {
        printf("ERROR: input file not specified\n");
        data.error = true;
    } else 
    if (data.n < 1)
    {
        printf("ERROR: N has to be positive");
        data.error = true;
    }

    return data;
}
void create_table(int n, int iter)
{
    int cnt, i, j;
    int *cardset = (int*) malloc(n * sizeof(int));
    int *data = (int*) malloc(iter * sizeof(int));
    fill_with(data, iter, 0);

    // print table head
    puts("  N  |  count");
    puts("----------------------------");

    for (i = 1; i < n+1; i++)
    {
        for (j = 0; j < iter; j++)
        {
            fill(cardset, i);
            shuffle(cardset, i);
            
            for (cnt = 1; !inorder(cardset, i); cnt++)
                shuffle(cardset, i);

            data[j] = cnt;
            printf("                         \r");
            printf(" % 3d | %d\r", i, cnt);
        }
        printf(" % 3d | %d\n", i, average(data, iter));
    }

    free(cardset);
    free(data);
}

int main(int argc, char **argv)
{
    struct args args = parse_args(argc, argv);
    if (args.error)
        return 1;

    // hide console cursor
    hidecursor();

    // set seed for random
    srand(time(NULL));

    //if (args.print_table)
        create_table(args.n, args.iterations);
}
