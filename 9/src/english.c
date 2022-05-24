#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#define N 26 // number of letters
#define ADD 5 // number of additional characters
#define DEFAULT_LEN 100
#define DEFAULT_OUTPUT_PATH "generated_englisch.txt"
#define CHARS N+ADD

struct args {
    // IO
    char *input_path;
    char *output_path;
    bool print_to_console;
    // behaviour
    int len;
    bool output_matrix;
    // Error/ControlFlow Handling
    char *error_msg[3];
    int error_level;
    bool help_printed;
};

struct matrix_wrapper {
    double content[CHARS][CHARS][CHARS+1];
};


struct args parse_args(int argc, char **argv)
{
    const char* const help_msg =
"\n\
Usage: %s [OPTIONS] INPUT_FILE\n\
\n\
Generates pseudo englisch based on a sample text\n\
\n\
Required Arguments:\n\
    INPUT_FILE  file to read sample text from\n\
    \n\
Optional Arguments:\n\
    -c          outputs to console (stdout) instead of output file,\n\
        overwrites -o\n\
    -h          shows this help message and exits\n\
    -l          specifies length of output text (in characters),\n\
         defaults to %d\n\
    -o          specifies path of output file, defaults to \"%s\"\
    -m          output probability matrix instead of generating text\n\
";
    char pos_input=0, pos_output=0;
    bool value_demanded=0;

    struct args data = {
        "",
        "",
        false,
        DEFAULT_LEN,
        false,
        {"", "", ""},
        0,
        false,
    };

    for (int i = 1; i < argc; i++)
    {
        if (data.error_level)
            break;
        
        if (argv[i][0] == '-')
        {
            if (value_demanded)
            {
                sprintf_s(data.error_msg[data.error_level], 50, "ERROR: Missing value for %s\n", argv[i-1]);
                data.error_level++;
            }
            switch(argv[i][1])
            {
                case 'c':
                    data.print_to_console = 1;
                break;
                case 'h':
                    printf(help_msg, argv[0], DEFAULT_LEN, DEFAULT_OUTPUT_PATH);
                    data.help_printed = true;
                    return data;
                break;
                case 'l':
                    data.len = atoi(argv[i+1]);
                    value_demanded = true;
                break;
                case 'm':
                    data.output_matrix = true;
                break;
                case 'o':
                    pos_output = i+1;
                    value_demanded = true;
                break;
                default:
                    sprintf_s(data.error_msg[data.error_level], 50, "ERROR: There's no option '%s'\n", argv[i]);
                    data.error_level++;
            }
        } else
        if (value_demanded)
            value_demanded = false;
        else
            pos_input = i;
    }

    if (!pos_input)
    {
        data.error_msg[data.error_level] = "ERROR: input file not specified\n";
        data.error_level++;
    }

    // Error Handling
    switch (data.error_level)
    {
        case 1:
            printf("An error has occured while passing arguments:\n");
            puts(data.error_msg[0]);
            printf("Use '%s -h' for detailed help\n", argv[0]);
            break;
        default:
            printf("%d errors have occured while passing arguments:\n", data.error_level);
            for (int i = 0; i < data.error_level; i++)
                printf("%d:\n%s", i, data.error_msg[i]);
            printf("Use '%s -h' for detailed help\n", argv[0]);
    }

    data.output_path = (pos_output) ? argv[pos_output] : DEFAULT_OUTPUT_PATH;
    data.input_path = argv[pos_input];
    return data;
}

struct matrix_wrapper fetch_matrix(FILE *input_file)
{
    struct matrix_wrapper data = {{{{0}}}};
    int bef_prev = 27, prev = 30, current;
    char c;

    // Character Reference
    /*
    a-z   0-25
    ,       26
    .       27
    !       28
    ?       29
    space   30
    */
    // TAB and NEWLINE are counted as space character
    // consecutive space characters are ignored

    while ((c = fgetc(input_file)) != EOF)
    {
        if (c >= 'A' && c <= 'Z')
            current = c - 'A';
        else
        if (c >= 'a' && c <= 'z')
            current = c - 'a';
        else
        if (c == ' ' || c == '\t' || c == '\n') 
        {
            if (prev == 30)
                continue;
            else
                current = 30;
        } else
            switch (c)
            {
                case ',':
                    current = 26;
                    break;
                case '.':
                    current = 27;
                    break;
                case '!':
                    current = 28;
                    break;
                case '?':
                    current = 29;
                    break;
                default:
                    continue;
            }
        data.content[bef_prev][prev][current]++;
        data.content[bef_prev][prev][CHARS]++;
        
        bef_prev = prev;
        prev = current;
    }
    fclose(input_file);
    return data;
}

void fractionize_matrix(double matrix[CHARS][CHARS][CHARS+1])
{
    for (int i = 0; i < CHARS; i++)
        for (int j = 0; j < CHARS; j++)
            for (int k = 0; k < CHARS; k++)
                if (matrix[i][j][CHARS] != 0)
                    matrix[i][j][k] /= matrix[i][j][CHARS];
}

void output_matrix(double matrix[CHARS][CHARS][CHARS+1], FILE *output_file)
{
    // fputs("// Last Element of each list is total count\n", output_file);
    // fprintf(output_file, "double probs[%d][%d][%d] =\n", CHARS, CHARS, CHARS);
    // fputc('{', output_file);
    // fputc('\n', output_file);

    for (int i = 0; i < CHARS; i++)
    {
        // fputs("    {\n", output_file);
        for (int j = 0; j < CHARS; j++)
        {
            // fputs("        {\n", output_file);
            for (int k = 0; k < CHARS; k++)
            {
                // if (k == 16)
                //     fputc('\n', output_file);
                fprintf(output_file, "%7.5lf ", matrix[i][j][k]);
            }
            fputc('\n', output_file);
        }
        fputc('\n', output_file);
    }
    // fputc('}', output_file);
    // fputc(';', output_file);
    fclose(output_file);
}

int generate_char(double prob[31])
{
    int r;
    long progress = 0;
        
    if (prob[31] == 0)
        return -1;

    r = rand();
    for (int c = 0; c < 31; c++)
    {
        if (r < RAND_MAX * prob[c] + progress)
            return c;

        progress += prob[c] * RAND_MAX;
    }

    return -1;
}

void generate_text(int len, double (*matrix)[CHARS][CHARS+1], FILE* output_file) 
{
    srand((unsigned)time(NULL));
    int bef_prev = 27, prev = 30, current;
    const char charmap[32] = "abcdefghijklmnopqrstuvwxyz,.!? ";
    char c;

    for (int i = 0; i < len; i++)
        // generate random char
        // based on probabilities found in matrix
    {
        // if an error occurs, retry
        while ( (current = generate_char(matrix[bef_prev][prev]) ) == -1);
        fputc(charmap[current], output_file);

        bef_prev = prev;
        prev = current;
    }
}


int main(int argc, char *argv[])
{   
    struct args args = parse_args(argc, argv);
    if (args.error_level)
        return args.error_level;
    if (args.help_printed)
        return 0;

    FILE *input_file = fopen(args.input_path, "r");
    FILE *output_file = args.print_to_console ? stdout : fopen(args.output_path, "w");

    double (*matrix)[CHARS][CHARS+1] = fetch_matrix(input_file).content;

    fractionize_matrix(matrix);

    if (args.output_matrix)
        output_matrix(matrix, output_file);
    else
        generate_text(args.len, matrix, output_file);

    return 0;
}
