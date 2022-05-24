#include <stdio.h>
#include <stdlib.h>

typedef struct dynamic_string {
    int len; // actual capacity
    int count; // number of elements contained
    char *data; // actual data
} dstr_t;

dstr_t *dl_create(int blocksize)
{
    dstr_t *list = (dstr_t*) malloc(sizeof(dstr_t));
    if (list == NULL)
    {
        printf("[WARNING]: Couldn't allocate dynamic string.");
        return NULL;
    }

    list->len = 1;
    list->count = 0;

    list->data = (char*) malloc(sizeof(char*));
    if (list->data == NULL)
    {
        printf("[WARNING]: Couldn't allocate space for dynamic string of length: %d", blocksize);
        free(list);
        return NULL;
    }
    return list;
}

static void dl_expand(dstr_t *list, int new_len)
{
    char *new_data = realloc(list->data, sizeof(char*) * new_len);
    if (new_data == NULL)
    {
        printf("[WARNING]: Couldn't reallocate dynamic string to new length: %d", new_len);
        free(list->data);
        free(list);
        return;
    }

    list->data = new_data;
    list->len = new_len;
}
