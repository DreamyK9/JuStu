#include <stdbool.h>

#ifndef _DYNAMIC_LIST_H
#define _DYNAMIC_LIST_H

/**
 * @brief interface for a dynamic list
 * 
 */
typedef struct list_key {
    struct list_key *next; // next element
    int value; // value
} key_t;

/**
 * @brief keys representing the chain elements
 *  inside a dynamic list
 */
typedef struct dynamic_list {
    int len;
    struct list_key *data;
} dlist_t;

/**
 * @brief create a dynamic list
 *
 * @return dlist_t* pointer to the new list
 */
dlist_t *dl_create();

/**
 * @brief adds value to end of list
 *
 * @param list list to add to
 * @param value value to be added
 * @return int - error code
 */
int dl_add(dlist_t *list, int value);

/**
 * @brief gets the value in a list at a specified index
 *
 * @param list list to get value from
 * @param index index of value to get
 * @return int - value
 */
int dl_get(dlist_t *list, int index);

/**
 * @brief free memory used by a list
 *
 * @param list list to free
 */
void dl_free(dlist_t *list);

/**
 * @brief swap the values at index 1 and index 2
 *
 * @param list list to swap in
 * @param index1 index of first value
 * @param index2 index of second value
 * @return int - error code
 */
int dl_swap(dlist_t *list, int index1, int index2);

/**
 * @brief insert a value at a given index
 *
 * @param list list to insert into
 * @param index index to insert at
 * @param value value to insert
 * @return int - error code
 */
int dl_insert(dlist_t *list, int index, int value);

/**
 * @brief delete value at a given index
 *
 * @param list list to delete from
 * @param index indext to delete at
 * @return int - error code
 */
int dl_delete(dlist_t *list, int index);

/**
 * @brief print all elements of a list
 *
 * @param list list to print elements of
 * @param sep string to seperate elements with
 */
void dl_print(dlist_t* list, char *sep);

#endif
