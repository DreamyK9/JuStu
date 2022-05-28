
#include <stdio.h>
#include <stdlib.h>

#include "../dynamic_list.h"

int dl_insert_lenn(dlist_t *list, int index, int value)
{
    // handle "index out of range" exceptions
    if (index > list->len || index < 0)
    {
        printf("[ERROR] Index out of range!\n");
        return 1;
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

    return 0;
}

int dl_delete_lenn(dlist_t *list, int index)
{
    // handle "index out of range" exceptions
    if (index > list->len || index < 0)
    {
        printf("[ERROR] Index out of range!\n");
        return 1;
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

    return 0;
}