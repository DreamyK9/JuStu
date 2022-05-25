#include <stdio.h>
#include <stdlib.h>

float data[31][31][31] = {{{0.0f}}};

void read_from_file(FILE *file)
{
    char c;
    char buffer[7];
    float number;

    // each block
    for (int b=0; b<31; b++)
    {
        // each line
        for (int l=0; l<31; l++)
        {
            // each number
            for (int n=0; n<31; n++)
            {
                // 7 characters per number
                for (int i=0; (c=fgetc(file)) != ' '; i++)
                    buffer[i] = c;
                
                number = strtof(buffer, NULL);
                data[b][l][n] = number;
            }
        }
        fgetc(file);
    }
    fgetc(file);
    fgetc(file);
}

int main()
{
    double total = 0.0;
    read_from_file(fopen("../data/matrix.txt", "r"));

    for (int i=0; i<31; i++)
    {
        for (int j=0; j<31; j++)
        {
            for (int k=0; k<31; k++)
            {
                total += data[i][j][k];
            }
            if (j == 16)
                putchar('\n');
            printf("%7.4f ", total);
            total = 0.0;
        }
    }
}
