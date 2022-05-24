#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define STD_OUTPATH "./data.txt"
/* ----------------------------- Data Structures ---------------------------- */
struct args {
    char *output_path;
    char *input_path;
    bool help_printed;
    bool print_console;
    bool error;
};

struct person {
    char fname[20];
    char lname[20];
    char matr_num[20];
    char birthyear[20];
};
/* ---------------------------- Utility Functions --------------------------- */
void goto_line(int line, FILE *file)
{
    char c;
    int l=0;
    rewind(file);

    for (;;)
    {
        if (l == line)
            break;
        
        c = fgetc(file);
        if ( c == '\n')
            l++;
    }
}
int get_file_length(FILE * file)
{
    int len=0, count=0;
    char c;
    
    // get number of persons
    do { c = fgetc(file);
    
        count++;
        if (c == '\n' || c == EOF)
        {
            count = 0;
            len++;
        }
    } while (c != EOF);

    if (count == 0)
        len--;

    rewind(file);
    return len;
}
void reset(char *buffer)
{
    int len = strlen(buffer);
    for (int i=0; i<len; i++)
        buffer[i] = 0;
}
void readln(struct person *p, FILE *file)
{
    char c, buffer[40] = {'\0'};
    int len=0, element=0;

    for (char c = fgetc(file);;c = fgetc(file))
    {
        if (c == ' ' || c == EOF || c == '\n')
        {
            switch(element)
            {
                case 0: strncpy_s(p->fname, sizeof(p->fname), buffer, 40);
                    break;
                case 1: strncpy_s(p->lname, sizeof(p->lname), buffer, 40);
                    break;
                case 2: strncpy_s(p->matr_num, sizeof(p->matr_num), buffer, 40);
                    break;
                case 3: strncpy_s(p->birthyear, sizeof(p->birthyear), buffer, 40);
            }
            element++;
            reset(buffer);
            len = 0;

            if (c == EOF || element > 3)
                break;
            else continue;
        }
        buffer[len++] = c;
    }
}
void writeln(struct person *p, FILE *file)
{
    fprintf(file, "%s %s %s %s\n", p->matr_num, p->fname, p->lname, p->birthyear);
}
/* ---------------------------- Process Function ---------------------------- */
struct args parse_args(int argc, char **argv)
{
    const char* const help_msg =
"\n\
Usage: %s [OPTIONS] INPUT_FILE\n\
\n\
reformats data\n\
\n\
Required Arguments:\n\
    INPUT_FILE  file to read data from\n\
    \n\
Optional Arguments:\n\
    -c          outputs to console (stdout) instead of output file,\n\
          overwrites -o\n\
    -h          shows this help message and exits\n\
    -o          specifies path of output file, defaults to \"%s\"\
";
    struct args data = {"", "", false, false, false};

    bool value_demanded = false;
    char pos_input=0, pos_output=0;

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
                    printf(help_msg, argv[0], STD_OUTPATH);
                    data.help_printed = true;
                    return data;
                break;
                case 'o':
                    pos_output = i+1;
                    value_demanded = true;
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
            pos_input = i;
    }

    if (!pos_input)
    {
        printf("ERROR: input file not specified\n");
        data.error = true;
        return data;
    }

    data.input_path = argv[pos_input];
    data.output_path = pos_output ? argv[pos_output] : STD_OUTPATH;
    return data;
}
void process_data(FILE *input_file, FILE *output_file)
{
    char c;
    unsigned int line_count = get_file_length(input_file);
    struct person p = {0, 0, 0, 0};

    // read and write data
    for (int i = 0; i < line_count; i++)
    {
        goto_line(i ,input_file);
        readln(&p, input_file);
        goto_line(line_count - i, input_file);
        writeln(&p, output_file);
    }
}

int main(int argc, char **argv)
{
    struct args args = parse_args(argc, argv);
    if (args.error)
        return 1;
    if (args.help_printed)
        return 0;

    FILE *input_file = fopen(args.input_path, "r");
    FILE *output_file = args.print_console ? stdout : fopen(args.output_path, "w");

    process_data(input_file, output_file);
}
