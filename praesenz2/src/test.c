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
    /////////////////////
    printf("Original: ");
    dl_print(list, ", ");
    putchar('\n');

    // swap function
    dl_swap(list, 1, 3);
    /////////////////////
    printf("Post Swap: ");
    dl_print(list, ", ");
    putchar('\n');

    // insert function
    dl_insert(list, 0, 10);
    dl_insert(list, 3, 11);
    /////////////////////
    printf("Post Insert: ");
    dl_print(list, ", ");
    putchar('\n');


    // delete function
    dl_delete(list, 0);
    dl_delete(list, 2);
    /////////////////////
    printf("Post Deletion: ");
    dl_print(list, ", ");
    putchar('\n');

    // swap back
    dl_swap(list, 1, 3);
    /////////////////////
    printf("Back to original: ");
    dl_print(list, ", ");
    putchar('\n');
}
