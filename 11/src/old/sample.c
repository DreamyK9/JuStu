#include<stdbool.h>
#include <stdlib.h>

struct empty_list_key{
    int offest;
    struct empty_list_key* next;
};

typedef struct list_t{
    int CURRENT_POSITION; //position of the array cursor.
    int BLOCK_SIZE; //size of data type
    int SIZE;
    void** data;
    struct empty_list_key* empty_keys;
}list_t;

list_t* init_list(int size, int blocksize){
    if(size < 0){
        return NULL;
    }
    list_t *list = malloc(sizeof(list_t));
    if(list == NULL){
        return NULL;
    }
    list->CURRENT_POSITION = 0;
    list->BLOCK_SIZE = blocksize;
    list->SIZE = size;
    list->data = malloc(sizeof(void*) * size);
    if(list->data == NULL){
        free(list);
        return NULL;
    }
    if(size > 0){
        int i;
        struct empty_list_key* empty_key;
        empty_key = malloc(sizeof(struct empty_list_key));
        //TODO: Check for NULL. If NULL, cleanup everything and return.
        empty_key->offest = 0;
        if(size > 1){
            for(i = 1; i < size; i++){
                empty_key->next = malloc(sizeof(struct empty_list_key));
                //TODO: Check for NULL. If NULL, cleanup everything and return.
                empty_key = empty_key->next;
                empty_key->offest = i;
            }
        }
    }else{
        list->empty_keys = NULL;
    }
    return list;
}

void delete_list(list_t* list){
    free(list->data);
    free(list);
}

bool list_set(list_t* list, int pos, void* value){
    if(pos < list->SIZE && pos >= 0){
        list->data[pos] = value;
        return true;
    }else{
        return false;
    }
}
bool list_unset(list_t* list, int pos){
    if(pos < list->SIZE && pos >= 0){
        free(list->data[sizeof(void*) * pos]);
        list->data[pos] = NULL;
        struct empty_list_key* empty_key = malloc(sizeof(struct empty_list_key));
        if(empty_key == NULL){
            return false;
        }

        //insert empty key at beginning of empty keys linked list.
        empty_key->offest = pos;
        empty_key->next = list->empty_keys;
        list->empty_keys = empty_key;
        return true;
    }else{
        return false;
    }
}

void* list_get(list_t* list, int pos){
    if(pos < list->SIZE && pos >= 0){
        return list->data[pos];
    }else{
        return NULL;
    }
}

bool list_push(list_t* list,void* value){
    void** tmp = realloc(list->data,(sizeof(void*) * list->SIZE) + sizeof(void*));
    if(tmp == NULL){
        return false;
    }else{
        list->data = tmp;
        list->SIZE ++;
        list_set(list,list->SIZE-1,value);
        return true;
    }
}

void* list_pop(list_t* list){
    void* value = list_get(list,list->SIZE-1);
    void** tmp = realloc(list->data,(sizeof(void*) * (list->SIZE ) ));
    if(tmp == NULL){
        return NULL;
    }else{
        list->SIZE --;
        list->data = tmp;
        return value;
    }
}

int list_size(list_t* list){
    return list->SIZE;
}

bool list_add(list_t* list, void* value){
    if(list->empty_keys == NULL){
        return list_push(list,value);
    }else{
        int offset = list->empty_keys->offest;
        struct empty_list_key* empty_key = list->empty_keys->next;
        free(list->empty_keys);
        list->empty_keys = empty_key;
        return list_set(list,offset,value);
    }
}

bool list_remove(list_t* list, int pos){
    struct empty_list_key* empty_key = malloc(sizeof(struct empty_list_key));
    if(empty_key == NULL)   return false;

    if(list_unset(list,pos)){
        empty_key->offest = pos;
        empty_key->next = list->empty_keys;
        list->empty_keys = empty_key;
        return true;
    }else{
        return false;
    }
}
