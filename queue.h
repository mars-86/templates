#ifndef __TEMPLATE_QUEUE_INCLUDED_H__
#define __TEMPLATE_QUEUE_INCLUDED_H__

#include <stdio.h>

#define TEMPLATE_VAL(v) \
    &v, sizeof(v)

typedef struct queue queue_t;

queue_t* queue_create(size_t size);
void queue_enqueue(queue_t* queue, void* val, size_t size);
int queue_dequeue(queue_t* queue, void* rmval);
void queue_clear(queue_t* queue);
void queue_print(queue_t* queue, void (*print_fn)(const void* val));
size_t queue_size(queue_t* queue);
void queue_delete(queue_t* queue);

#endif // __TEMPLATE_QUEUE_INCLUDED_H__