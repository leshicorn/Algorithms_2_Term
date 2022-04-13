/*
На вход программы подаётся число отделений 2 <= N <= 1000000, за которым следует
N капиталов отделений 1 <= Ci <= 1000000.
T — минимальная сумма из возможных, которую должна заплатить брокерам фирма
«Котлетный рай», с двумя знаками после запятой. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef long long int T;

typedef struct binary_heap
{
    T* body;
    size_t allocated;
    size_t nodes;
    int type;
} binary_heap;

binary_heap* bh_create(size_t maxsize, int type)
{
    binary_heap* t = malloc(sizeof(binary_heap));

    t->body = malloc((maxsize + 1) * sizeof(T));
    t->allocated = maxsize;
    t->nodes = 0;
    t->type = type;

    return t;
}

void bh_destroy(binary_heap* t)
{
    free(t->body);
    free(t);
}

void bh_swap(binary_heap* t, int a, int b)
{
    T tmp = t->body[a];
    t->body[a] = t->body[b];
    t->body[b] = tmp;
}

T bh_get(binary_heap* t)
{
    assert(t->nodes > 0);
    return t->body[1];
}

void bh_siftUp(binary_heap* t, size_t index)
{
    if (t->type == 0)
    {
        for (size_t i = index; i > 1 && t->body[i] < t->body[i / 2]; i /= 2)
        {
            bh_swap(t, i, i / 2);
        }
    }
    else
    {
        for (size_t i = index; i > 1 && t->body[i] > t->body[i / 2]; i /= 2)
        {
            bh_swap(t, i, i / 2);
        }
    }
}

void bh_insert(binary_heap* t, T node)
{
    assert(t->nodes < t->allocated);
    t->body[++t->nodes] = node;
    
    bh_siftUp(t, t->nodes);
}

void bh_siftDown(binary_heap* t, size_t index){
    if (t->type == 0)
    {
        while (1)
        {
            size_t left = index + index;
            size_t right = left + 1;
            size_t smallest = index;

            if (left <= t->nodes && t->body[left] < t->body[index])
                smallest = left;
            if (right <= t->nodes && t->body[right] < t->body[smallest])
                smallest = right;
            if (smallest == index)
                break;
            bh_swap(t, index, smallest);
            index = smallest;
        }
    }
    else
    {
        while (1)
        {
            size_t left = index + index;
            size_t right = left + 1;
            size_t smallest = index;
            if (left <= t->nodes && t->body[left] > t->body[index])
                smallest = left;
            if (right <= t->nodes && t->body[right] > t->body[smallest])
                smallest = right;
            if (smallest == index)
                break;
            bh_swap(t, index, smallest);
            index = smallest;
        }
    }
}

void bh_remove(binary_heap* t) {
    assert(t->nodes > 0);
    t->body[1] = t->body[t->nodes];
    t->nodes--;
    bh_siftDown(t, 1);
}

void bh_merge(binary_heap* t, binary_heap* tmp)
{
    for (int i = 1; i <= (int)tmp->nodes; i++)
    {
        bh_insert(t, tmp->body[i]);
    }
    tmp->nodes = 0;
}

int main() {
    int N = 0;
    scanf("%d", &N);
    binary_heap* heap = bh_create(N, 0);
    T tmp = 0;
    for (int i = 0; i < N; i++) {
        scanf("%lld", &tmp);
        bh_insert(heap, tmp);
    }
    double sum = 0;
    while (heap->nodes != 1) {
        tmp = bh_get(heap);
        bh_remove(heap);
        tmp += bh_get(heap);
        bh_remove(heap);
        sum += tmp * 0.01;
        bh_insert(heap, tmp);
    }
    printf("%.2lf\n", sum);
    bh_destroy(heap);
    return 0;
}

/*
Сложность работы по времени O(N * logN)
Сложность работы по памяти O(N)
*/
