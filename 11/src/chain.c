#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1028

typedef struct list_key {
    struct list_key *next;
    char value;
} key_t;

typedef struct dynamic_list {
    int len;
    struct list_key *data;
} dlist_t;

dlist_t *dl_init()
{
    
}

int dl_add(dlist_t *list, char value)
{
    key_t *key = list->data;
    for (int i = 1; i < list->len; i++)
    {
        key = key->next;
    }

    key->next = (key_t *) malloc(sizeof(key_t));
    key->next->value = value;
    list->len++;
}

char *read_line(FILE *input_file)
{
    char buffer[BUFFER_SIZE] = fgets(buffer, BUFFER_SIZE, input_file);
    int len = 0;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        if (buffer[i] == NULL)
        {
            len = i;
            break;
        }
    }
    char *str = (char *) malloc(len * sizeof(char));
    return str;
}
