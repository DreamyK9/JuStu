#include <stdio.h>
#include <stdlib.h>

#include "dynamic_list.h"

int main()
{
    dlist_t *list = dl_create();
    dl_add(list, 1);
    dl_add(list, 2);
    dl_add(list, 3);
    dl_add(list, 4);

    dl_swap(list, 1, 3);
    dl_print(list, "\n");
}
