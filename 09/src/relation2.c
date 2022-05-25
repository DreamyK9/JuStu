#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#define DEFAULT_OUTPUT_PATH "new_relation.txt"
/* -------------------------------------------------------------------------- */
struct args {
    // IO
    char *input_path, *output_path;
    bool print_to_console;
    // Error Handling
    char *error_msg[3];
    int error_level;
    bool help_printed;
};
struct matrix {
    double **data;
    int len;
    int width;
};
struct input_wrapper {
    struct matrix *matrix;
    char *error_msg;
    int error_level;
};
struct cnt_array {
    double *data;
    int len;
};
/* ---------------------------- Utility Functions --------------------------- */
int allocate_matrix(struct matrix *matrix)
{
    if (!matrix->len)
    {
        printf("WARNING: Matrix couldn't be allocated");
        return 2;
    }

    matrix->data = malloc(matrix->len * sizeof(double*));
    
    if (!matrix->width)
        return 1;

    for (int i=0; i < matrix->len; i++)
        matrix->data[i] = malloc(matrix->width * sizeof(double));

    return 0;
}
void freematrix(struct matrix* matrix)
{
    if (matrix->width)
        for (int i=0; i < matrix->len; i++)
            free(matrix->data[i]);

    free(matrix->data);
}
void clear_buffer(char *buffer, int len)
{
    for (int i=0; i < len; i++)
        buffer[i] = '\0';
}
bool contains(double* set, double value)
{
    bool iscontained = false;
    // TODO: test this
    // ? Does this work
    for (int i=0; i < sizeof(set[0])/sizeof(set); i++)
        if (set[i] == value)
            iscontained = true;

    return iscontained;
}
/*int sum(int start, int end)
{
    int sum = 0;
    for (int i=start; i < end; i++)
        sum += i;
    
    return sum;
}
*/
/* --------------------------- Procedure Functions -------------------------- */
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
    -o          specifies path of output file, defaults to \"%s\"\
";

    unsigned int pos_input=0, pos_output=0;
    bool value_demanded = false;

    struct args data = {
        // IO
        "", "",
        false,
        // Error Handling
        {"", "", ""},
        0,
        false
    };

    /* ----------------------------- Arg Processing ----------------------------- */
    for (int i=1; i<argc; i++)
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
                // print to console
                case 'c':
                    data.print_to_console = 1;
                    break;
                // print help
                case 'h':
                    printf(help_msg, argv[0], DEFAULT_OUTPUT_PATH);
                    data.help_printed = true;
                    return data;
                // specify output file
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

    /* ----------------------------- Error Handling ----------------------------- */
        if (data.error_level ==  1)
        {
            printf("An error has occured while passing arguments:\n");
            puts(data.error_msg[0]);
            printf("Use '%s -h' for detailed help\n", argv[0]);
        } else
        if (data.error_level > 1)
        {
            printf("%d errors have occured while passing arguments:\n", data.error_level);
            for (int i = 0; i < data.error_level; i++)
                printf("%d: %s", i, data.error_msg[i]);
            printf("Use '%s -h' for detailed help\n", argv[0]);
        }

    data.input_path = argv[pos_input];
    data.output_path = (pos_output) ? argv[pos_output] : DEFAULT_OUTPUT_PATH;
    return data;
}
struct input_wrapper parse_input(FILE *input_file)
{
    // ASSERTS FOLLOWING FORMATTING OF INPUT DATA
    /*
    element1: set1 set2 set3 ... setn
    ...
    elementn: set1 set2 set3 ... setn


    Example (3 sets with 4 elements in relation):
    """
    1 13 27
    4 13 38
    24 6 9
    50 14 27

    """

    Elements of the relation are seperated by
    lines, while values from the sets inside
    the relation's elements are sepparated
    by spaces.
    */
    // UNEXPECTED BEHAVIOUR MIGHT OCCUR
    // IF INPUT IS INCORRECTLY FORMATTED

    static struct matrix relation = {NULL, 0, 0};
    struct input_wrapper wrapper = {&relation, "", 0};
    int count=0;
    char c;

    // throw error if input_file is empty
    if (fgetc(input_file) == EOF)
    {   
        wrapper.error_level = 2;
        wrapper.error_msg = "ERROR: Input file is empty!";
        puts(wrapper.error_msg);
        return wrapper;
    }

    // get number of sets involved in relation
    do {
        c = fgetc(input_file);
        count++;

        if (!isdigit(c) && count > 1)
            relation.width++, count=0;

    } while (c != '\n' && c != EOF);

    rewind(input_file);

    // get number of elements in the relation
    do {
        count++;
        if ((c == '\n' || c == EOF) && count > 1)
            relation.len++, count=0;

    } while (c = fgetc(input_file), c != EOF);

    // throw error if no elements found
    if (!(relation.len && relation.width))
    {
        wrapper.error_level = 1;
        wrapper.error_msg = "ERROR: No elements found in input file!";
        puts(wrapper.error_msg);
        return wrapper;
    }

    rewind(input_file);
    
    // store the relation
    allocate_matrix(&relation);
    char buffer[32] = {0};
    unsigned int relation_pos=0, buffer_pos=0;

    for (int i = 0; c = fgetc(input_file), c != EOF; i++)
    {
        if (c == '\n')
        {
            relation.data[(int)relation_pos/relation.len][relation_pos%relation.width] = strtod(buffer, NULL);
            relation_pos++;
            clear_buffer(buffer, 32);
        }
        else
            buffer[buffer_pos++] = c;
    }

    return wrapper;
}
struct matrix filter_relation(struct matrix* relation)
{   
    // * create list of all contained components
    // decrarations and initializations
    struct cnt_array elements = {NULL, 0};
    int elements_maxlen = relation->len * relation->width;
    elements.data = (double*) malloc(elements_maxlen * sizeof(double));
    for (int i = 0; i < elements_maxlen; i++)
        elements.data[i] = 0;
    // processing

    for (int i = 0; i < relation->len; i++)
        for (int j = 0; j < relation->width; j++)
            if (!contains(elements.data, relation->data[i][j]))
                elements.data[elements.len++] = relation->data[i][j];
    
    struct matrix new_relation = {NULL, 0};
    new_relation.len = pow(elements.len, relation->width);
    new_relation.width = relation->width;
    allocate_matrix(&new_relation);

    for (int i = 0; i < relation->len; i++);
        
    /** 
     // TODO: create new relation
     * * 1: add all reflexive parts
     * * 2: add original non-reflexive parts
     * * 3: add missing transitive parts
     */

    free(elements.data);
    freematrix(&new_relation);
}
void output_relation(struct matrix* relation,FILE *output_file)
{
    // TODO: output relation
}

/* -------------------------------------------------------------------------- */
/* ------------------------------- Entry Point ------------------------------ */
int main(int argc, char**argv)
{
    struct args args = parse_args(argc, argv);
    if (args.error_level)
        return args.error_level;
    if (args.help_printed)
        return 0;
    
    FILE *input_file = fopen(args.input_path, "r");
    FILE *output_file = args.print_to_console ? stdout : fopen(args.output_path, "w");

    struct input_wrapper input = parse_input(input_file);
    if (input.error_level)
        return input.error_level;
    
    struct matrix filtered_relation = filter_relation(input.matrix);

    output_relation(&filtered_relation, output_file);
}
