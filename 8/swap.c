#include <stdio.h>
#define N 8

void swap(int *a, int *b);
void swaparr(int *arr1, int *arr2);

char *help_msg = "\
%s swaps the contents of two number arrays\n\
arrays are hardcoded\n\n\
Usage: %s [OPTIONS]\n\n\
Options:\n\
    -h  show this help message\n\
";

int main(int argc, char *argv[])
{
    /* Argument Processing */
    /////////////////////////
    for (int i=1; i<argc; i++)
    {
        if (argv[i][0] == '-')
            switch (argv[i][1])
            {
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
    
    /* Create the two arrays */
    ///////////////////////////
    int array1[N] = {1, 2, 3, 4, 5, 6, 7, 8};
    int array2[N] = {2, 4, 6, 8, 10, 12, 14, 16};


    /* Print BEFORE */
    //////////////////
    puts("BEFORE");

    printf("Array 1: ");
    for (int i=0; i<N; i++) printf("%02d ", array1[i]);
    putchar('\n');
    
    printf("Array 2: ");
    for (int i=0; i<N; i++) printf("%02d ", array2[i]);
    putchar('\n');


    /* Swap the two arrays */
    /////////////////////////
    swaparr(array1, array2);


    /* Print AFTER */
    /////////////////
    puts("\nAFTER");

    printf("Array 1: ");
    for (int i=0; i<N; i++) printf("%02d ", array1[i]);
    putchar('\n');
    
    printf("Array 2: ");
    for (int i=0; i<N; i++) printf("%02d ", array2[i]);
    putchar('\n');

}

// swap 2 arrays' contents
void swaparr(int *arr1, int *arr2) {
    for (int i=0; i<N; i++) {
        swap(&arr1[i], &arr2[i]);
    }
}

// swap two variables' values
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
