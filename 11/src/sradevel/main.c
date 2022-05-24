#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dyn_list.h"

int main(int argc, char** argv)
{
    dynamic_list* l = dl_create(2);

    int item1 = 1;
    int item2 = 2;
    int item3 = 3;

    dl_add(l, &item1);    
    dl_add(l, &item2);
    dl_add(l, &item3);

    assert(dl_length(l) == 3);
    assert(l->size == 4);

    int* result = (int*) dl_get(l, 2);
    assert(*result == 3);

    dl_set(l, &item1, 0);
    result = dl_get(l, 0);
    assert(*result == 1);

    dl_remove(l, 3);
    dl_remove(l, 2);
    dl_remove(l, 1);
    assert(dl_length(l) == 0);

    dynamic_list* l2 = dl_create(2);
    dl_add(l2, &item1);
    dl_add(l2, &item2);

    dl_add(l, &item1);    
    dl_add(l, &item2);
    dl_add(l, &item3);

    dl_append(l, l2);
    assert(dl_length(l) == 5);

    dl_free(l);
    dl_free(l2);

    printf("all tests passed!\n");

    return 0;
}
