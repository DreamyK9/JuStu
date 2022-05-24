#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define DEFAULT_OUTPUT_PATH "new_relation.txt"

struct args {
    // IO
    char *input_path, *output_path;
    bool print_to_console;
    // behaviour
    // Error/ControlFlow Handling
    char *error_msg[3];
    int error_level;
    bool help_printed;
};

struct smart_relation {
    double **array;
    int len;
};

struct smart_filter {
    bool* array;
    int count;
};

struct smart_array {
    double *array;
    int len;
};

struct smart_array2d {
    double **array;
    int *len_of;
    int len;
};

struct relation_data {
    // original relation
    struct smart_relation relation;
    // filtered relation
    double **filtered;
    // number of elements in relation
    // (size of top level array)
    int element_count;
    // number of sets involved
    // (size of second level arrays)
    int set_count;
};

struct relation_wrapper {
    struct relation_data data;
    int error_level;
};


double **allocate_relation(element_count, set_count)
{
    double **relation = (double**)malloc(element_count * sizeof(double*));

    for (int i = 0; i < element_count; i++)
        relation[i] = (double*)malloc(set_count * sizeof(double));
        
    return relation;
}

struct smart_array2d allocate_smart_array2d(int len, int sub_len)
{
    struct smart_array2d array2d = {NULL, NULL, 0};
    
    if (len < 1)
        puts("WARNING: Returned unallocated Array");
        return array2d;

    array2d.array = (double**)malloc(len * sizeof(double*));
    array2d.len_of = (int*)malloc(len * sizeof(int));
    array2d.len = len;

    if (sub_len)
        for (int i = 0; i < len; i++)
        {
            array2d.array[i] = (double*)malloc(sub_len * sizeof(double));
        }

    return array2d;
}

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
    char pos_input=0, pos_output=0;
    bool value_demanded=0;

    struct args data = {
        "",
        "",
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
                    printf(help_msg, argv[0], DEFAULT_OUTPUT_PATH);
                    data.help_printed = true;
                    return data;
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
                printf("%d: %s", i, data.error_msg[i]);
            printf("Use '%s -h' for detailed help\n", argv[0]);
    }

    data.output_path = (pos_output) ? argv[pos_output] : DEFAULT_OUTPUT_PATH;
    data.input_path = argv[pos_input];
    return data;
}

struct relation_wrapper parse_input(FILE *input_file)
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
    // IF FORMATTING IS INCORRECT

    struct relation_data data = {{NULL, 0}, NULL, 0, 0};
    char c;

    // throw error if input_file is empty
    if (fgetc(input_file) == EOF)
    {
        puts("ERROR: Input file is empty");
        struct relation_wrapper wrapper = {data, 1};
        return wrapper;
    }

    // get number of sets involved in relation
    int char_count = 0;
    do {
        c = fgetc(input_file);
        char_count++;

        if ((c == ' ' || c == '\n' || c == EOF) && char_count > 0)
            data.set_count++, char_count=0;

    } while (c != '\n' && c != EOF);

    rewind(input_file);

    // get number of elements the relation has
    while ((c = fgetc(input_file)) != EOF)
        if (c == '\n')
            data.element_count++;

    // throwh error if the number of
    // elements can't be properly read
    if (data.set_count == 0 || data.element_count == 0)
    {
        puts("ERROR: Input file doesn't contain any elements");
        struct relation_wrapper wrapper = {data, 1};
        return wrapper;
    }

    rewind(input_file);

    // store the relation
    data.relation.array = allocate_relation(data.element_count, data.set_count);
    char buffer[32] = {0};

    for (int i = 0; (c = fgetc(input_file)) != EOF; i++)
    {
        if (c == '\n')
        {
            data.relation.array[(int)data.relation.len/data.set_count][data.relation.len%data.set_count] = strtod(buffer, NULL);

            for (int b = 0; b<32; b++, buffer[b] = 0)
                if (buffer[b] == '\0')
                    break;
        }
        else
            buffer[i] = c;
    }

    struct relation_wrapper wrapper = {data, 0};
    return wrapper;
}

void filter_relation(struct relation_data *data)
{   
    // filters the relation to produce its
    // reflexive transitive hull
    // output is assigned to "filtered"
    // attribute of relation_data

    struct smart_filter reflexive_filter = {NULL, 0};
    reflexive_filter.array = (bool*)malloc(data->element_count * sizeof(bool));

    // fill filter for reflexive elements
    for (int i = 0; i < data->element_count; i++)
    {
        reflexive_filter.array[i] = true;
        for (int j = 0; j < data->set_count-1; j++)
        {
            if (data->relation.array[i][j] != data->relation.array[i][j+1])
                reflexive_filter.array[i] = false;
            
            if (reflexive_filter.array[i])
                reflexive_filter.count++;
        }
    }

    if (reflexive_filter.count == 0)
    {
        free(reflexive_filter.array);
        return;
    }

    // split reflexive elements and the rest each in a new array
    struct smart_array reflexive = {NULL, 0};
    reflexive.array = (double *)malloc(reflexive_filter.count * sizeof(double));
    struct smart_relation rest = {NULL, 0};
    rest.array = allocate_relation(data->element_count - reflexive_filter.count, data->set_count);

    for (int i = 0; i < data->element_count; i++)
    {
        if (reflexive_filter.array[i])
            reflexive.array[reflexive.len++] = data->relation.array[i][0];
        else
            rest.array[rest.len++] = data->relation.array[i];
    }

    free(reflexive_filter.array);

    // loop through remaining (non-reflexive) elements
    // to find transitive value groups
    struct smart_array2d trans_map = allocate_smart_array2d(reflexive.len, rest.len);

    for (int i = 0; i < reflexive.len; i++)
        for (int j = 0; j < rest.len; j++)
        {
            if (reflexive.array[i] == rest.array[j][0])
                trans_map.array[i][trans_map.len_of[i]++] = rest.array[j][1];
            else
            if (reflexive.array[i] == rest.array[j][1])
                trans_map.array[i][trans_map.len_of[i]++] = rest.array[j][0];
        }

    // freeing allocated memory
    for (int i = 0; i < trans_map.len; i++)
        free(trans_map.array[i]);

    free(trans_map.array);
    free(reflexive.array);
    free(rest.array);
}

void output_relation(struct relation_data data, FILE *output_file)
{
    
}

int main(int argc, char **argv)
{
    struct args args = parse_args(argc, argv);
    if (args.error_level)
        return args.error_level;
    if (args.help_printed)
        return 0;
    
    FILE *input_file = fopen(args.input_path, "r");
    FILE *output_file = args.print_to_console ? stdout : fopen(args.output_path, "w");

    struct relation_wrapper relation = parse_input(input_file);
    if (relation.error_level)
        return relation.error_level;

    struct relation_data data = relation.data;
    filter_relation(&data);
    if (!data.filtered)
        puts("INFO: Your relation has no reflexive transitive components.");
    
    output_relation(data, output_file);
    free(data.relation.array);
}
