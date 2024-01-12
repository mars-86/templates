#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __TYPE_CHECK(a, b) \
    if (b && a != b)       \
        return;

#define __DELETE_NODE(n) \
    do {                 \
        n->next = NULL;  \
        free(n->val);    \
        free(n);         \
    } while (0)

typedef struct list_node list_node_t;

struct list_node {
    void* val;
    list_node_t* next;
};

struct list {
    list_node_t* begin;
    list_node_t* end;
    size_t length;
    size_t size;
};

list_t* list_create(size_t size)
{
    list_t* __l = (list_t*)malloc(sizeof(list_t));

    __l->begin = __l->end = NULL;
    __l->length = 0;
    __l->size = size;

    return __l;
}

void list_insert(list_t* list, void* val, size_t size)
{
    __TYPE_CHECK(list->size, size)
    list_node_t* __node = (list_node_t*)malloc(sizeof(list_node_t));
    __node->val = malloc(list->size);

    memcpy(__node->val, val, list->size);
    __node->next = NULL;

    if (!list->begin) {
        list->begin = __node;
        list->end = list->begin;
    } else {
        list->end->next = __node;
        list->end = list->end->next;
    }
    list->length++;
}

int list_remove(list_t* list, const void* val, void* rmval, int (*remove_fn)(const void* lsval, const void* rmval))
{
    list_node_t *__curptr = list->begin, *__prvptr = NULL;
    int __rmval = 0;

    while (__curptr != NULL) {
        __rmval = remove_fn(__curptr->val, val);
        if (__rmval) {
            if (!__prvptr) {
                list->begin = __curptr->next;
            } else {
                __prvptr->next = __curptr->next;
            }
            if (rmval)
                memcpy(rmval, __curptr->val, list->size);
            __DELETE_NODE(__curptr);
            list->length--;
            return 1;
        }
        __prvptr = __curptr;
        __curptr = __curptr->next;
    }

    return 0;
}

void list_clear(list_t* list)
{
    list_node_t *__curptr, *__nxtptr;
    __curptr = list->begin;

    while (__curptr != NULL) {
        __nxtptr = __curptr->next;
        __DELETE_NODE(__curptr);
        __curptr = __nxtptr;
    }
}

void list_print(list_t* list, void (*print_fn)(const void* val))
{
    list_node_t* __curptr = list->begin;

    while (__curptr != NULL) {
        print_fn(__curptr->val);
        __curptr = __curptr->next;
    }
}

size_t list_size(list_t* list)
{
    return list->length;
}

void list_delete(list_t* list)
{
    list_clear(list);
    free((list_t*)list);
}