#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dynlist_str.h"

dlist_t *dl_create()
{
    // allocate and initialize new list
    dlist_t *list = (dlist_t *) malloc(sizeof(dlist_t));
    if (list == NULL)
        return NULL;
    list->len = 0;

    // allocate and initialize first list key
    list->data = malloc(sizeof(key_t));
    if (list->data == NULL)
    {
        free(list);
        return NULL;
    }
    list->data->next = NULL;
    list->data->value = NULL;

    return list;
}

int dl_add(dlist_t *list, char* value)
{
    // get last key
    key_t *key = list->data;
    while (key->next)
        key = key->next;

    // add new key at end of the chain if last key's value isn't empty
    if (key->value != NULL)
    {
        key->next = (key_t *) malloc(sizeof(key_t));
        if (key->next == NULL)
            return 1;
        key = key->next;
        key->next = NULL;
    }

    key->value = value;
    list->len++;
    return 0;
}

char *dl_get(dlist_t *list, int index)
{
    // handle "index out of range"
    if (index > list->len || index < 0)
        return NULL;

    // get key at index
    key_t *key = list->data;
    for (int i = 0; i < index; i++)
        key = key->next;

    return key->value;
}

void dl_delete(dlist_t *list)
{
    // free all stored values
    for (int i = list->len-1; i > -1; i--)
    {
        key_t *key = list->data;
        for (int j = 0; j < i; j++)
            key = key->next;
        free(key);
    }

    free(list);
}

dlist_t *dl_merge(dlist_t *source1, dlist_t *source2)
{
    dlist_t *dest = dl_create();

    // add all items from first source to destination
    key_t *key = source1->data;
    for (int i = 0; i < source1->len; i++)
    {
        dl_add(dest, key->value);
        key = key->next;
    }
    // add all items from second source to destination
    key = source2->data;
    for (int i = 0; i < source2->len; i++)
    {
        dl_add(dest, key->value);
        key = key->next;
    }

    // set length for destination list
    dest->len = source1->len + source2->len;

    // delete source lists, so the values are not double referenced
    dl_delete(source1);
    dl_delete(source2);

    return dest;
}

int dl_split(dlist_t *source, dlist_t *dest1, dlist_t *dest2)
{
    // Warn if destination lists aren't empty
    if (dest1->len > 0)
        printf("[Warning]: destination 1 is not empty");
    if (dest2->len > 0)
        printf("[Warning]: destination 2 is not empty");

    // if uneven, make first list longer
    // if even, both are same length
    int len1 = (int) ceil((double) source->len/2);
    int len2 = (source->len - source->len%2) / 2;

    // add first half of source list to destination 1
    key_t *key = source->data;
    for (int i = 0; i < len1; i++)
    {
        dl_add(dest1, key->value);
        key = key->next;
    }
    // add second half of source list to destination 2
    for (int i = 0; i < len2; i++)
    {
        dl_add(dest2, key->value);
        key = key->next;
    }

    // delete source list, so the values are not double referenced
    dl_delete(source);

    return 0;
}

void dl_print(dlist_t* list, char *sep)
{
    key_t *key = list->data;
    for (int i = 0; i < list->len; i++)
    {
        printf("%s%s", key->value, sep);
        key = key->next;
    }
}
