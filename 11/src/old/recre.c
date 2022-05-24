#include<stdbool.h>
#include <stdlib.h>

struct empty_list_key {
    int offset;
    struct empty_list_key *next;
};

typedef struct list_t {
    int CURRENT_POS;
    int BLOCK_SIZE;
    int SIZE;
    void **data;
    struct empty_list_key *empty_keys;
} list_t;

// create new list
list_t *init_list(int size, int blocksize)
{
    if (size < 0)
        return NULL;

    // initialize list object
    list_t *list = malloc(sizeof(list_t));
    //TODO: check if '!' works here instead of '== NULL'
    if (!list)
        return NULL;
    list->CURRENT_POS = 0;
    list->BLOCK_SIZE = blocksize;
    list->SIZE = size;
    list->data = malloc(sizeof(void*) * size);
    if (!list->data)
    {
        free(list);
        return NULL;
    }
    for (int i = 0; i < size; i++)
        list->data[i] = NULL;

    // allocate memory for list items
    if (size > 0)
    {
        struct empty_list_key *empty_key;
        empty_key = malloc(sizeof(struct empty_list_key));
        if (!empty_key)
            return NULL;
        empty_key->offset = 0;
        list->empty_keys = empty_key;
        if (size > 1)
            for (int i = 1; i < size; i++)
            {
                empty_key->next = malloc(sizeof(struct empty_list_key));
                if (!empty_key)
                    return NULL;
                empty_key = empty_key->next;
                empty_key->offset = i;
            }
        else
            list->empty_keys = NULL;
    }
    return list;
}

// delete list
void delete_list(list_t *list)
{
    free(list->data);
    free(list);
}

// set pos to value
bool list_set(list_t *list, int pos, void *value)
{
    if (pos < 0 || pos >= list->SIZE)
        return false;

    list->data[pos] = value;
    return true;
}

// free pos
bool list_unset(list_t *list, int pos)
{
    if (pos < 0 || pos >= list->SIZE)
        return false;

    free(list->data[sizeof(void*) * pos]);
    list->data[pos] = NULL;
    struct empty_list_key *empty_key = malloc(sizeof(struct empty_list_key));
    if (!empty_key)
        return false;

    // insert empty key at beginning of empty keys list
    empty_key->offset = pos;
    empty_key->next = list->empty_keys;
    list->empty_keys = empty_key;
    return true;
}

// get value at pos
void *list_get(list_t *list, int pos)
{
    if (pos < 0 || pos >= list->SIZE)
        return NULL;

    return list->data[pos];
}

// add value at the end
bool list_push(list_t *list, void *value)
{
    void **tmp = realloc(list->data, sizeof(void*) * list->SIZE + sizeof(void *));
    if (!tmp)
        return false;
    list->data = tmp;
    list->SIZE++;
    list_set(list, list->SIZE-1, value);

}
