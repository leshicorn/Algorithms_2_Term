#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct binary_heap 
{
    int* body;
    size_t allocated;
    size_t nodes;
    int type;
} bh;

bh* bh_create(size_t maxsize, int type) 
{
    bh* heap = malloc(sizeof(bh));
    heap->body = malloc((maxsize + 1) * sizeof(int));
    heap->allocated = maxsize;
    heap->nodes = 0;
    heap->type = type;
    return heap;
}

void bh_destroy(bh* heap) 
{
    free(heap->body);
    free(heap);
}

void bh_swap(bh* heap, int a, int b) 
{
    int tmp = heap->body[a];
    heap->body[a] = heap->body[b];
    heap->body[b] = tmp;
}

int bh_get(bh* heap) 
{
    assert(heap->nodes > 0);
    return heap->body[1];
}

void bh_siftUp(bh* heap, size_t index) 
{
    if (heap->type == 0) 
    {
        for (size_t i = index; i > 1 && heap->body[i] < heap->body[i / 2]; i /= 2) 
        {
            bh_swap(heap, i, i / 2);
        }
    } 
    else
    {
        for (size_t i = index; i > 1 && heap->body[i] > heap->body[i / 2]; i /= 2) 
        {
            bh_swap(heap, i, i / 2);
        }
        
    }
}

void bh_insert(bh* heap, int node) 
{
    assert(heap->nodes < heap->allocated);
    heap->body[++heap->nodes] = node;
    bh_siftUp(heap, heap->nodes);
}

void bh_siftDown(bh* heap, size_t index) 
{
    if (heap->type == 0) 
    {
        for (;;) {
            size_t left = index + index;
            size_t right = left + 1;
            size_t smallest = index;
            if (left <= heap->nodes && heap->body[left] < heap->body[index])
            {
                smallest = left;
            }
            if (right <= heap->nodes && heap->body[right] < heap->body[smallest])
            {
                smallest = right;
            }
            if (smallest == index)
            {
                break;
            }
            bh_swap(heap, index, smallest);
            index = smallest;
        }
    }
    else 
    {
        for (;;) 
        {
            size_t left = index + index;
            size_t right = left + 1;
            size_t smallest = index;
            if (left <= heap->nodes && heap->body[left] > heap->body[index])
            {
                smallest = left;
            }
            if (right <= heap->nodes && heap->body[right] > heap->body[smallest])
            {
                smallest = right;
            }
            if (smallest == index)
            {
                break;
            }
            bh_swap(heap, index, smallest);
            index = smallest;
        }
    }
}

void bh_remove(bh* heap) 
{
    assert(heap->nodes > 0);
    heap->body[1] = heap->body[heap->nodes];
    heap->nodes--;
    bh_siftDown(heap, 1);
}

void bh_merge(bh* heap, bh* tmp) 
{
    for (int i = 1; i <= (int)tmp->nodes; i++) 
    {
        bh_insert(heap, tmp->body[i]);
    }
    tmp->nodes = 0;
}

int main() 
{
    int n = 0;
    scanf("%d", &n);
    bh** heap = malloc(n * sizeof(bh));
    char flag = 0;
    int index = 0, type = 0, elem = 0;
    size_t size = 0;
    while ((flag = getchar()) != -1) 
    {
        switch (flag) 
        {
            case '0':
            {
                scanf("%d%ld%d", &index ,&size, &type);
                heap[index] = bh_create(size, type);
                break;
            }
            case '1':
            {
                scanf("%d%d", &index, &elem);
                bh_insert(heap[index], elem);
                break;
            }
            case '2':
            {
                scanf("%d", &index);
                printf("%d\n", bh_get(heap[index]));
                break;
            }
            case '3':
            {
                scanf("%d", &index);
                bh_remove(heap[index]);
                break;
            }
            case '4':
            {
                scanf("%d", &index);
                printf("%ld\n", heap[index]->nodes);
                break;
            }
            case '5':
            {
                scanf("%d%d", &index, &elem);
                bh_merge(heap[index], heap[elem]);
                break;
            }
            case '6':
            {
                scanf("%d", &index);
                bh_destroy(heap[index]);
                break;
            }
        }
    }
    free(heap);
    return 0;
}