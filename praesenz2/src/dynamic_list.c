#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "dynamic_list.h"

dlist_t *dl_create()
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

int dl_add(dlist_t *list, int value)
{
    // get last key
    key_t *key = list->data;
    while (key->next)
        key = key->next;

    // add new key at end of the chain if last key's value isn't empty
    if (key->used)
    {
        key->next = (key_t *) malloc(sizeof(key_t));
        if (key->next == NULL)
            return 1;
        key = key->next;
        key->next = NULL;
        key->used = true;
    }

    key->value = value;
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

    // get key before index
    key_t *key = list->data;
    for (int i = 0; i < index-1; i++)
        key = key->next;

    // save pointer to beginning of rest of the list
    key_t *tmp = key->next;

    // insert new key
    key->next = (key_t *) malloc(sizeof(key_t));
    if (key->next == NULL)
        return 1;

    // if index is 0, update list->data
    if (index == 0)
        list->data = key;

    // initialize inserted key
    key = key->next;
    key->next = tmp;
    key->used = true;
    key->value = value;

    // update length
    list->len++;

    return 0;
}

int dl_delete(dlist_t *list, int index)
{
    
}

int dl_insert_lenn(dlist_t *list, int index, int value)
{
    // handle "index out of range" exceptions
    if (index > list->len || index < 0)
    {
        printf("[ERROR] Index out of range!\n");
        return 0;
    }

    if(index==0)
    {
        key_t *tmpnext=list->data;
        list->data = (key_t *) malloc(sizeof(key_t));
        key_t *key=list->data;
        key->value=value;
        key->next=tmpnext;
    }
    else
    {
        key_t *key = list->data;
        // find element before index
        for (int i = 0; i < index-1; i++)
            key = key->next;

        key_t *tmpnext=key->next;
        key->next = (key_t *) malloc(sizeof(key_t));
        key=key->next;
        key->value=value;
        key->next=tmpnext;
    }
    list->len++;
}

int dl_delete_lenn(dlist_t *list, int index)
{
    // handle "index out of range" exceptions
    if (index > list->len || index < 0)
    {
        printf("[ERROR] Index out of range!\n");
        return 0;
    }

    if(index==0)
    {
        key_t *key=list->data;
        key_t *tmp=list->data->next;
        key->next = key->next->next;
        key->value=tmp->value;
        free(tmp);
    }
    else
    {
        key_t *key = list->data;
        // find key before index
        for (int i = 0; i < index-1; i++)
            key = key->next;
        key_t *tmp=key->next;
        key->next = key->next->next;
        free(tmp);
    }

    list->len--;
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
