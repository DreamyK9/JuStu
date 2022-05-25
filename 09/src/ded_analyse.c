#include <stdio.h>
#include <string.h>
#define N 26 // number of letters
#define ADD 4 // number of additional characters
#define VALUES_PER_LINE 5
#define DEFAULT_OUTPUT_PATH "./output_language.txt"
#define DEFAULT_MODE "freq"
#define CHARS 2*N+ADD

/* Custom Data Types */

// Frequency list with total count
struct freq_data {
    double list[N];
    double count;
};


// Probability matrix with total count
struct prob_data {
    double matrix[CHARS][CHARS][CHARS];
    double count;
};

/* Function Declarations */

/**
 * @brief Total Letter Count Only
 * 
 * @param input_file File to read from
 * @return long 
 */
long op_count(FILE* input_file);

/* Process Functions */

/**
 * @brief List of absolute letter counts
 * 
 * @param input_file 
 * @return struct freq_data
 */
struct freq_data op_freq_abs(FILE *input_file);

/**
 * @brief List of relative letter counts (as percentages)
 * 
 * @param input_file File to read from
 * @return struct freq_data 
 */
struct freq_data op_freq(FILE *input_file);

/**
 * @brief Absolute probability matrix
 * 
 * @param input_file File to read from
 * @return struct prob_data
 */
struct prob_data op_prob_abs(FILE *input_file);

/**
 * @brief Relative probability matrix (as percentages)
 * 
 * @param input_file File to read from
 * @return struct prob_data 
 */
struct prob_data op_prob(FILE *input_file);

/**
 * @brief Output any type of freq data
 * 
 * @param data data to output
 * @param file file to output to
 * @param absolute bool specifying, whether values are absoulute or relative
 */
void output_freq(struct freq_data data, FILE *file, int absolute);

/**
 * @brief Output any type of prob data
 * 
 * @param data data to output
 * @param file file to output to
 * @param absolute bool specifying, whether values are absoulute or relative
 */
void output_prob(struct prob_data data, FILE *file, int absolute);


char const help_msg[999] =
"Usage: %s [OPTIONS] INPUT_FILE\n\
\n\
Reads a text from a file and analyses it depending on operation mode\n\
\n\
Required Arguments:\n\
    INPUT_FILE  file to read input from\n\
    \n\
Optional Arguments:\n\
    -c          output to console (stdout) instead of output file,\n\
        overwrites -o\n\
    -h          show this help message and exit\n\
    -m          specify mode to run in, defaults to \"%s\"\n\
    -o          specify path of output file, defaults to \"%s\"\n\
    \n\
Operation modes:\n\
    Operation modes specify the way the input is processed\n\
    and therefore what is output\n\
    \n\
    freq        Analyse frequency of letters present (as percentage)\n\
    freq_abs    Output frequencies as absolute values instead\n\
    prob        Outputs a 3d-matrix of the probability of a character\n\
            following a sequence of two specific other characters\n\
            (only includes letters and punctuation marks)\n\
    prob_abs    Output probabilities as absolute values instead\n\
    count       Counts the number of words\n\
    \
";


int main(int argc, char *argv[])
{   
    puts("This program was executed.");
    //TODO: outsource input processing
    /* Input Processing Vars */
    // positions in argv[]
    int pos_input=0, pos_output=0, pos_mode=0;
    // boolean values
    int value_demanded=0, print_to_console=0, read_from_console=0;

    /* Input Processing */ {

        for (int i = 1; i < argc; i++)
        {
            if (argv[i][0] == '-')
            {
                if (value_demanded)
                {
                    printf("ERROR: Missing value for %s\n", argv[i-1]);
                    printf("Use '%s -h' for detailed help\n", argv[0]);
                    return 1;
                }
                switch(argv[i][1])
                {
                    // specify output path
                    case 'o':
                        pos_output = i+1;
                        value_demanded = 1;
                    break;
                    // show help
                    case 'h':
                        printf(help_msg, argv[0], DEFAULT_MODE, DEFAULT_OUTPUT_PATH);
                        return 0;
                    // output to console instead of output file
                    // overwrites -o
                    case 'c':
                        print_to_console = 1;
                    break;
                    // choose operation mode
                    case 'm':
                        pos_mode = i+1;
                        value_demanded = 1;
                    break;
                    /////
                    default:
                        printf("ERROR: There's no option '%s'\n", argv[i]);
                        printf("Use '%s -h' for detailed help\n", argv[0]);
                        return 1;
                }
            } else
            if (value_demanded)
                value_demanded = 0;
            else
                pos_input = i;
        }

        if (pos_input == 0)
        {
            puts("ERROR: input file not specified");
            printf("Use '%s -h' for detailed help\n", argv[0]);
            return 1;
        }
    }

    ///////////////////////

    /* Data Processing*/ {
        // operation mode
        char *mode = (pos_mode) ? argv[pos_mode] : DEFAULT_MODE;
        // path for output file
        char *output_path = (pos_output) ? argv[pos_output] : DEFAULT_OUTPUT_PATH;
        FILE *output_file = (print_to_console) ? stdout : fopen(output_path, "w");
        FILE *input_file = fopen(argv[pos_input], "r");
        
        // Mode Switch
            if (strcmp(mode, "freq") == 0)
                output_freq(op_freq(input_file), output_file, 0);
        else
            if (strcmp(mode, "prob"))
                output_prob(op_prob(input_file), output_file, 0);
        else
            if (strcmp(mode, "count") == 0)
                fprintf(output_file, "%ld", op_count(input_file));
        else
            if (strcmp(mode, "freq_abs"))
                output_freq(op_freq_abs(input_file), output_file, 1);
        else
            if (strcmp(mode, "prob_abs"))
                output_prob(op_prob_abs(input_file), output_file, 1);
        
        fputc('\n', output_file);
        fclose(output_file);
    }
    return 0;
}

struct freq_data op_freq_abs(FILE *input_file)
{
    struct freq_data data = {{0}, 0};
    char c, isletter=0;
    
    
    while ((c = fgetc(input_file)) != EOF)
    {
            // convert uppercase letters to lowercase
            c += (c >= 'A' && c <= 'Z') * ('a' - 'A');
            
            // if c is letter
            isletter = (c >= 'a' && c <= 'z');
            // increment frequency counter letter counter 
            data.list[c - 'a']+= isletter;
            data.count+= isletter;
    }
    fclose(input_file);
    return data;
}

struct freq_data op_freq(FILE *input_file)
{
    struct freq_data data = op_freq_abs(input_file);

    /* Calculating Ratios */
    data.count /= 100;

    for (int i=0; i<26; i++)
        data.list[i] /= data.count;

    data.count *= 100;
    return data;
}

struct prob_data op_prob_abs(FILE *input_file)
{

    // Character Reference
    /*
    A-Z      0-25
    a-z     26-51
    .       52
    !       53
    ?       54
    space   55
    */
    
    struct prob_data data = {{{{0}}}, 0};
    char bef_prev = 52, prev = 55, current;
    char c;

    while ((c = fgetc(input_file)) != EOF)
    {
        if (c >= 'A' && c <= 'Z')
        {
            current = c - 'A';
        } else
        if (c >= 'a' && c <= 'z')
        {
            current = c - 'a' + 26;
        } else
        if (c == '.')
        {
            current = 26;
        } else
        if (c == '!')
        {
            current = 27;
        } else
        if (c == '?')
        {
            current = 28;
        } else
        // TAB or space
        if (c == 9 || c == ' ')
        {
            current = 29;
        }
        else {
            continue;
        }
        data.matrix[bef_prev][prev][current]++;
        data.count++;
        
        // shift current to prev
        // and prev to bef_prev
        bef_prev = prev;
        prev = current;
    }
    fclose(input_file);
    return data;
}

struct prob_data op_prob(FILE *input_file)
{
    struct prob_data data = op_prob_abs(input_file);

    data.count /= 100;

    for (int i=0; i<26; i++)
    {
        for (int j=0; j<26; j++)
        {
            for (int k=0; k<26; k++)
            {
                data.matrix[i][j][k] /= data.count;
            }
        }
    }
    data.count *= 100;
    return data;
}

long op_count(FILE* input_file)
{
    char c;
    long count = 0;
    while ((c = fgetc(input_file)) != EOF)
    {   
        // convert all upper to lowercase
        c += (c >= 'A' && c <= 'Z') * ('a' - 'A');
        // 
        count += (c >= 'a' && c <= 'z');
    }
    fclose(input_file);
    return count;
}

// Output Functions
void output_freq(struct freq_data data, FILE *file, int absolute)
{
    // Formatting
    char *format;
    if (absolute)
        format = "%d, ";
    else
        format = "%5.2f, ";

    // Printing
    fputc('{', file);
    for (int i = 0; i < 26; i++)
    {
        if (i % VALUES_PER_LINE == 0) fputc('\n', file);
        fprintf(file, format, data.list[i]);
    }
    fputc('}', file);
}

void output_prob(struct prob_data data, FILE *file, int absolute)
{
    // Formatting
    char *format;
    if (absolute)
        format = "%d, ";
    else
        format = "%5.2f, ";

    // Printing
    fputc('{', file);
    for (int i = 0; i < 26; i++)
    {
        fputc('{', file);
        for (int j = 0; j < 26; j++)
        {
            fputc('{', file);
            for (int k = 0; k < 26; k++)
            {
                if (k % VALUES_PER_LINE == 0 && k!=0) fputc('\n', file);
                fprintf(file, format, data.matrix[i][j][k]);
            }
            fprintf(file, "}, ");
        }
        fprintf(file, "}, ");
    }
    fputc('}', file);
}
