/**
 * @file dynstr.h
 * @author Jonas Wolf
 * @brief single-chained dynamic list of strings
 * @version 0.1
 * @date 2022-05-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _DYNLIST_STR_H
#define _DYNLIST_STR_H

/**
 * @brief data structure used by the dynamic list as chain elements
 *
 */
typedef struct list_key {
    struct list_key *next; // next element
    char *value; // string value
} key_t;

/**
 * @brief data structure representing the list itself
 *
 */
typedef struct dynamic_list {
    int len;
    struct list_key *data;
} dlist_t;

/**
 * @brief creates a new dynamic list
 *
 * @return dlist_t* - ptr to new list
 */
dlist_t *dl_create();

/**
 * @brief adds an element to the end of a list
 *
 * @param list list to add to
 * @param value value to add
 * @return int - error code
 */
int dl_add(dlist_t *list, char* value);

/**
 * @brief gets value at index
 *
 * @param list list to get value from
 * @param index index to get value at
 * @return char*
 */
char *dl_get(dlist_t *list, int index);

/**
 * @brief delete a list, freeing all memory used by it
 *
 * @param list list to delete
 */
void dl_delete(dlist_t *list);

/**
 * @brief merge two dynamic lists
 *
 * @param source1 first half list
 * @param source2 second half list
 * @param dest destination list
 * @return dlist_t - new merged dynamic list
 */
dlist_t *dl_merge(dlist_t *source1, dlist_t *source2);

/**
 * @brief split dynamic in two new lists
 *
 * @param source list to be split
 * @param dest1 list to store first half in
 * @param dest2 list to store second half in
 * @return int - error code
 */
int dl_split(dlist_t *source, dlist_t *dest1, dlist_t *dest2);

/**
 * @brief print all elements of a list
 *
 * @param list list to print elements of
 * @param sep string to seperate elements with
 */
void dl_print(dlist_t* list, char *sep);

#endif
