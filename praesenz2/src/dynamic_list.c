#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dynamic_list.h"

dlist_t *dl_create()
{
    // allocate new list
    dlist_t *list = (dlist_t *) malloc(sizeof(dlist_t));
    if (list == NULL)
        return NULL;

    //initialize new list
    list->len = 0;
    list->data = NULL;

    return list;
}

int dl_add(dlist_t *list, int value)
{
    // get last key
    key_t *key = list->data;
    while (key->next)
        key = key->next;

    // add new key at end of the chain
    key->next = (key_t *) malloc(sizeof(key_t));
    if (key->next == NULL)
        return 1;
    key = key->next;
    key->next = NULL;

    // add value to new key
    key->value = value;

    // update length
    list->len++;

    return 0;
}

int dl_get(dlist_t  *list, int index)
{
    // handle "index out of range" exceptions
    if (index > list->len || index < 0)
    {
        printf("[ERROR] Index out of range!\n");
        return 0;
    }

    // get key at index
    key_t *key = list->data;
    for (int i = 0; i < index; i++)
        key = key->next;

    return key->value;
}

void dl_free(dlist_t *list)
{
    key_t *key = list->data;
    key_t *next;

    // free all keys
    for (int i = 0; i < list->len; i++)
    {
        next = key->next;
        free(key);
        key = next;
    }

    free(list);
}

int dl_swap(dlist_t *list, int index1, int index2)
{
    // handle "index out of range" exceptions
    if (index1 > list->len || index1 < 0)
    {
        printf("[ERROR]: Index out of range!\n");
        return 1;
    }
    if (index2 > list->len || index2 < 0)
    {
        printf("[ERROR]: Index out of range!\n");
        return 1;
    }

    // get key at index1
    key_t *key1 = list->data;
    for (int i = 0; i < index1; i++)
        key1 = key1->next;

    // get key at index2
    key_t *key2 = list->data;
    for (int i = 0; i < index2; i++)
        key2 = key2->next;

    // swap values
    int temp = key1->value;
    key1->value = key2->value;
    key2->value = temp;

    return 0;
}

int dl_insert(dlist_t *list, int index, int value)
{
    // handle "index out of range" exceptions
    if (index > list->len || index < 0)
    {
        printf("[ERROR]: Index out of range!\n");
        return 1;
    }

    // generate new key and add value to it
    key_t *new_key = (key_t *) malloc(sizeof(key_t));
    if (new_key == NULL)
        return 1;
    new_key->value = value;

    if (index == 0)
    {
        // insert at beginning
        new_key->next = list->data;
        list->data = new_key;
    }
    else
    {
        // get key before index
        key_t *prev = list->data;
        for (int i = 0; i < index-1; i++)
            prev = prev->next;

        // insert at index
        new_key->next = prev->next;
        prev->next = new_key;
    }

    // update length
    list->len++;

    return 0;
}

int dl_delete(dlist_t *list, int index)
{
    // handle "index out of range" exceptions
    if (index > list->len || index < 0)
    {
        printf("[ERROR] Index out of range!\n");
        return 1;
    }

    key_t *old;

    // delete key
    if (index == 0)
    {
        // delete at beginning
        old = list->data;
        list->data = list->data->next;
    }
    else
    {
        // get key before index
        key_t *prev = list->data;
        for (int i = 0; i < index-1; i++)
            prev = prev->next;

        old = prev->next;

        // delete at index
        prev->next = old->next;
    }

    // update length
    list->len--;

    free(old);
    return 0;
}


void dl_print(dlist_t* list, char *sep)
{
    key_t *key = list->data;
    for (int i = 0; i < list->len; i++)
    {
        printf("%d%s", key->value, sep);
        key = key->next;
    }
}
