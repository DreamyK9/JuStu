#include <stdio.h>
#include <stdlib.h>

#include "dyn_list.h"

dynamic_list* dl_create(int initial_size)
{
    dynamic_list* lst = (dynamic_list*) malloc(sizeof(dynamic_list));
    if (lst == NULL)
    {
        fprintf(stderr, "Couldn't allocate dynamic list.");
        exit(1);
    }

    lst->size = initial_size;
    lst->chunk_size = initial_size;
    lst->count = 0;

    lst->items = malloc(sizeof(void*) * initial_size);
    if (lst->items == NULL)
    {
        fprintf(stderr, "Couldn't allocate space for dynmic list of size: %d", initial_size);
        exit(1);
    }

    return lst;
}

static void dl_expand(dynamic_list* lst, int new_size)
{
    void** new_items = realloc(lst->items, sizeof(void*) * new_size);
    if (new_items == NULL)
    {
        fprintf(stderr, "Couldn' realloc space for list of size %d", new_size);
        exit(1);
    }

    lst->items = new_items;
    lst->size = new_size;
}

void dl_add(dynamic_list* lst, void* item)
{
    if (lst->count == lst->size)
        dl_expand(lst, lst->size + lst->chunk_size);
    
    lst->items[lst->count++] = item;
}

void dl_set(dynamic_list* lst, void* item, int index)
{
    if(index > lst->size)
    {
        fprintf(stderr, "Index out of bounds.\n");
        exit(1);
    }

    lst->items[index] = item;
}

void dl_append(dynamic_list* lst1, dynamic_list* lst2)
{
    for (int i=0; i<dl_length(lst2); i++)
        dl_add(lst1, dl_get(lst2, i));
}

void* dl_get(dynamic_list* lst, int index)
{
    if (index > lst->count)
    {
        fprintf(stderr, "Index out of bounds.\n");
        exit(1);
    }

    return lst->items[index];
}

void dl_remove(dynamic_list* lst, int index)
{
    if (index > lst->count)
    {
        fprintf(stderr, "Index out of bounds.\n");
        exit(1);
    }
    
    lst->items[index] = NULL;
    for (int i=index; i<=lst->count - 1; i++)
    {
        lst->items[i] = lst->items[i + 1];
        lst->items[i + 1] = NULL;
    }

    lst->count--;
}

int dl_length(dynamic_list* lst)
{
    return lst->count;
}

void dl_free(dynamic_list* lst)
{
    free(lst->items);
    free(lst);
}

