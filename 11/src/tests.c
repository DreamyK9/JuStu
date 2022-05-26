#include <stdlib.h>
#include <stdio.h>
#include "dynlist_str.h"

int main()
{
    dlist_t *list[8] = {NULL};

    // create list
    list[0] = dl_create();
    dl_add(list[0], "I just picked up a new job");
    dl_add(list[0], "But I'm hoping it ain't hard");
    dl_add(list[0], "After all it's a night shift");
    dl_add(list[0], "I'll be working the graveyard");
    puts("**list 0:");
    dl_print(list[0], "\n");

    // create another list
    list[1] = dl_create();
    dl_add(list[1], "Urban legends aside");
    dl_add(list[1], "I think I'll be fine");
    dl_add(list[1], "There's no way these things are alive");
    puts("**list 1:");
    dl_print(list[1], "\n");

    // merge lists
    list[2] = dl_merge(list[0], list[1]);
    puts("**list 2:");
    dl_print(list[2], "\n");

    // split uneven
    list[3] = dl_create();
    list[4] = dl_create();
    dl_split(list[2], list[3], list[4]);
    puts("**list 3:");
    dl_print(list[3], "\n");
    puts("**list 4:");
    dl_print(list[4], "\n");

    // create a third list
    list[5] = dl_create();
    dl_add(list[5], "Take you with me on the way down");
    dl_add(list[5], "I'm laying low");
    dl_add(list[5], "There's nothing I can say now");
    dl_add(list[5], "You don't already know");
    puts("**list 5:");
    dl_print(list[5], "\n");

    // split even
    list[6] = dl_create();
    list[7] = dl_create();
    dl_split(list[5], list[6], list[7]);
    puts("**list 6:");
    dl_print(list[6], "\n");
    puts("**list 7:");
    dl_print(list[7], "\n");
}
