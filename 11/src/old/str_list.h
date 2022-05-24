#pragma once
#ifndef _LIST_H
#define _LIST_H

typedef struct list_t {
    char **data;
    unsigned int BLOCK_SIZE;
    unsigned long LEN;
} list_t;

list_t *create_list(unsigned long len, unsigned int blocksize);

#endif
