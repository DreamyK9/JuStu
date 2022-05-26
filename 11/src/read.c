#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 2048

#include "dynlist_str.h"
/* ----------------------------- Data Structures ---------------------------- */
struct args {
    // IO
    char *in_path;
    char *out_path;
    // Error & Control Flow Handling
    char *error_msg[64];
    int error_level;
    bool help_printed;
};

/* -------------------------------- Functions ------------------------------- */
char *readline(FILE *input_file)
{
    // read line from input file to fixed size buffer
    char buffer[BUFFER_SIZE] = {0};
    fgets(buffer, BUFFER_SIZE, input_file);
    if (*buffer == 0)
        return NULL;

    // get actual length of read line inside the buffer
    int len = strlen(buffer) + 1; // +1 because strlen doens't include \0
    if (len == 0)
        return NULL;

    // allcoate space to hold line
    char *str = (char *) malloc(len * sizeof(char));
    if (str == NULL)
        return NULL;

    // copy buffer to new space
    for (int i = 0; i < len; i++)
        str[i] = buffer[i];

    return str;
}

struct args parse_args(int argc, char **argv)
{
    const char* const help_msg =
"\n\
Usage: %s [OPTIONS] INPUT_FILE\n\
\n\
Reads a file line by line into a dynamic_list\n\
and outputs them again afterwards\n\
\n\
Required Arguments:\n\
    INPUT_FILE  file to read from\n\
    \n\
Optional Arguments:\n\
    -h          shows this help message and exits\n\
    -o          specifies path of output file, uses\n\
        stdout if not specified\
";

    bool value_demanded=0;
    struct args data = {
        NULL,
        NULL,
        {NULL},
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
                break;
                case 'h':
                    printf(help_msg, argv[0]);
                    data.help_printed = true;
                    return data;
                break;
                case 'o':
                    data.out_path = argv[i+1];
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
                data.in_path = argv[i];
    }

    if (!data.in_path)
    {
        data.error_msg[data.error_level] = "ERROR: input file not specified\n";
        data.error_level++;
    }

    // Error Handling
    switch (data.error_level)
    {
        case 0:
            break;
        case 1:
            printf("An error has occured while parsing arguments:\n");
            puts(data.error_msg[0]);
            printf("Use '%s -h' for detailed help\n", argv[0]);
            break;
        default:
            printf("%d errors have occured while parsing arguments:\n", data.error_level);
            for (int i = 0; i < data.error_level; i++)
                printf("%d:\n%s", i, data.error_msg[i]);
            printf("Use '%s -h' for detailed help\n", argv[0]);
    }
    return data;
}
/* ------------------------------- Entry Point ------------------------------ */
int main(int argc, char **argv)
{
    // parse and handle command line arguments
    struct args args = parse_args(argc, argv);
    if (args.error_level)
        return args.error_level;
    if (args.help_printed)
        return 0;

    // create file objects for io
    FILE *in_file = fopen(args.in_path, "r");
    FILE *out_file = args.out_path ? fopen(args.out_path, "w") : stdout;

    // create dynamic list
    dlist_t *list = dl_create();
    if (list == NULL)
    {
        printf("Error: Could not initialize list");
        return 1;
    }

    // read line by line from input file and store resulting strings to dynamic list
    char *str;
    for (int l = 0, feedback; (str = readline(in_file)); l++)
    {
        feedback = dl_add(list, str);
        if (feedback > 0)
        {
            printf("[WARNING]: Line %d couldn't be read.", l);
            free(str);
        }
    }

    // output values in dynamic list
    for (int i = 0; i < list->len; i++)
        fprintf(out_file, dl_get(list, i));

    dl_delete(list);
}
