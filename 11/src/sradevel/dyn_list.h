/**
 * simple dynamic list
 */

#ifndef _DYN_LIST_H
#define _DYN_LIST_H

/**
 * Dynamic list structure
 *
 * chunk_size: chunks of data which gets allocated
 *             is set by dl_create to the initial_size
 * size:       capacity of the dynamic list, grows by 
 *             chunk_size elements
 * count:      number of actual stored items
 * items:      actual stored items
 */
typedef struct dyn_list_s {
    int chunk_size;
    int size;
    int count;
    void** items;
} dynamic_list;

/**
 * creates a dynamic list
 *
 * initial_size: the initial count of elements, for which
 *               memory is allocated
 */
dynamic_list* dl_create(int initial_size);

/**
 * adds an item to the end of the list
 *
 * lst: the dynamic list
 * item: the item
 */
void dl_add(dynamic_list* lst, void* item);

/**
 * sets the item at an given index of the list
 *
 * lst: the dynamic list
 * item: the item to set
 * index: the item gets set at this index
 */
void dl_set(dynamic_list* lst, void* item, int index);

/**
 * appends another list to the dynamic list
 *
 * lst1: the list to append to
 * lst2: the list that gets appended
 */
void dl_append(dynamic_list* lst1, dynamic_list* lst2);

/**
 * retrieves an item of the index
 *
 * lst: the dynamic list
 * index: zero-based index of the item
 */
void* dl_get(dynamic_list* lst, int index);

/**
 * removes an item from the list, all subsequenced items
 * in the list gets shifted backwards (index - 1)
 *
 * lst: the dynamic list
 * index: the zero-based index of the item to be removed
 */
void dl_remove(dynamic_list* lst, int index);

/**
 * length (not size) of the dynamic list, aka
 * count of the stored elements
 *
 * lst: the dynmamic list
 *
 * returns the count of elements
 */
int dl_length(dynamic_list* lst);

/**
 * frees the list an its elements
 *
 * lst: the dynamic_list
 */
void dl_free(dynamic_list* lst);

#endif
