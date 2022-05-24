#include <stdlib.h>
#include <stdbool.h>

#include "str_list.h"

list_t *create_list(unsigned long init_len, unsigned int blocksize)
{
    if (init_len < 0 || blocksize < 1)
        return NULL;

    list_t *list = (list_t *) malloc(sizeof(list_t));
    if (list == NULL)
        return NULL;
    list->BLOCK_SIZE = blocksize;
    list->LEN = init_len;
    list->data = (char **) calloc(init_len, sizeof(void *));
    if (list->data == NULL)
        return NULL;

    if (init_len > 0)
    {
        for (int i = 0; i < init_len; i++)
        {
            list->data[i] = (char *) calloc(1, blocksize);
        }
    }
}
