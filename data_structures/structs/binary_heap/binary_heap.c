#include <stdio.h>
#include <stdlib.h>

#define error -1
#define success 0

typedef struct binary_heap_array
{
    int *body;
    size_t allocated;
    size_t nodes;
} bh;

bh* bh_create(size_t maxsize)
{
    bh *t = malloc(sizeof(bh));
    t -> body = malloc(sizeof(int) * (maxsize + 1));
    t -> allocated = maxsize;
    t -> nodes = 0;
    return t;
}

void bh_destroy(bh *t)
{
    free(t -> body); 
    free(t);
}

void bh_swap(bh *t, int a, int b)
{
    int tmp = t -> body[a];
    t -> body[b] = t -> body[a];
    t -> body[a] = tmp;
}

int main()
{

    return 0;
}