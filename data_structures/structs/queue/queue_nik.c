#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct queue
{
    void* data;
    size_t elem_size;
    size_t capacity;
    size_t used;
    size_t tail;
    size_t front;
};

struct queue*   queue_new(size_t elem_size);
int             queue_push(struct queue* q, const void* elem);
int             queue_pop(struct queue* q, void* elem);
int             queue_empty(struct queue const* q);
struct  queue*  queue_delete(struct queue* q);
void            queue_print(struct queue const* q, void (*pf) (void const* data));

struct queue* queue_new(size_t elem_size)
{
    struct queue* q = calloc(1, sizeof(struct queue));

    q->elem_size = elem_size;
    q->capacity = 0;
    q->used = 0;
    q->tail = 0;
    q->front = 0;

    return q;
}

int queue_push(struct queue* q, const void* elem)
{
    assert(q);
    assert(elem);

    if (q->capacity == 0)
    {   
        q->data = realloc(q->data, 4* q->elem_size);
        if (q->data == NULL)
        {
            return 1;
        }

        q->capacity = 4;
        q->used = 1;
        q->tail = 1;

        if (!memcpy(q->data, elem, q->elem_size))
        {
            return 1;
        }
        return 0;
    }

    if (q->capacity - 1 != q->used)
    {
        if (!memcpy(q->data + (q->tail* q->elem_size), elem, q->elem_size))
        {
            return 1;
        }

        q->tail = (q->tail + 1) % q->capacity;
        q->used++;

        return 0;
    }
    
    size_t last_capacity = q->capacity;
    q->capacity = q->capacity* 2;
    q->data = realloc(q->data, q->capacity* q->elem_size);
    
    if (q->data == NULL)
    {
        return 1;
    }

    if ((q->tail - q->front) == (last_capacity - 1))
    {
        if (!memcpy(q->data + (q->tail* q->elem_size), elem, q->elem_size))
        {
            return 1;
        }

        q->used++;
        q->tail++;

        return 0;
    }
    
    if (q->tail == 0)
    {
        q->tail = last_capacity;

        if (!memcpy(q->data + (q->tail* q->elem_size), elem, q->elem_size))
        {
            return 1;
        }

        q->used++;
        q->tail++;    

        return 0;
    }

    if (q->front >= last_capacity)
    {
        if (!memcpy(q->data + (q->capacity - last_capacity + q->front)* q->elem_size, q->data + q->front* q->elem_size, (last_capacity - q->front)* q->elem_size))
        {
            return 1;
        }

        if (!memcpy(q->data + q->tail* q->elem_size, elem, q->elem_size))
        {
            return 1;
        }

        q->tail++;
        q->used++;
        q->front = q->capacity - last_capacity + q->front;

        return 0;
    }

    if (!memcpy(q->data + last_capacity* q->elem_size, q->data, q->tail* q->elem_size))
    {
        return 1;
    }

    if (!memcpy(q->data + (last_capacity + q->tail)* q->elem_size, elem, q->elem_size))
    {
        return 1;
    }

    q->tail = last_capacity + q->tail + 1;
    q->used++;
    
    return 0;
}

int queue_pop(struct queue* q, void* elem)
{
    assert(q);
    assert(elem);

    if (q->used == 0)
    {
        return 1;
    }

    if (!memcpy(elem, q->data + (q->front* q->elem_size), q->elem_size))
    {
        return 1;
    }

    q->used--;
    q->front = (q->front + 1) % q->capacity;

    if (q->used == 0)
    {
        q->front = 0;
        q->tail = 0;
    }
    return 0;
}

int queue_empty(struct queue const* q)
{
    assert(q);
	
    if (q == NULL || q->used == 0)
    {
        return 1;
    }
    return 0;
}

struct queue* queue_delete(struct queue* q)
{
    assert(q);
	
    free(q->data);
    free(q);

    return NULL;
}

void queue_print(struct queue const* q, void (*pf) (void const* data))
{
    assert(q);

    printf("[");

    for(size_t i = 0; i < q->used; i++)
    {
        pf(q->data + ((q->tail - 1 - i + q->capacity* 2) % q->capacity)* q->elem_size);

        if (i != q->used - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}