#include <stdlib.h>

#include "../dynamic_list.h"

dlist_t *dl_create_old()
{
    // allocate and initialize new list
    dlist_t *list = (dlist_t *) malloc(sizeof(dlist_t));
    if (list == NULL)
        return NULL;
    list->len = 0;

    // allocate and initialize first list key
    list->data = (key_t *) malloc(sizeof(key_t));
    if (list->data == NULL)
    {
        free(list);
        return NULL;
    }
    list->data->next = NULL;
    list->data->value = 0;
    list->data->used = false;

    return list;
}
