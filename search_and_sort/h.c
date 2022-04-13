#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct my_heap{
    long long* heap;
    int sz;
} my_heap;

my_heap* create_heap(int new_size)
{
    my_heap* hp = (my_heap*) malloc(sizeof(my_heap));
    hp->heap = (long long*) malloc(sizeof(long long) * new_size);
    hp->sz = 0;
    return hp;
}

void delete_heap(my_heap* hp)
{
    free(hp->heap);
    hp->heap = NULL;
    free(hp);
    hp = NULL;
}

void swap(long long* a, long long* b)
{
    long long tmp = (*a);
    (*a) = (*b);
    (*b) = tmp;
}

void siftUp(my_heap* hp, int v)
{
    while(v > 1 && hp->heap[v / 2] > hp->heap[v])
    {
        swap(&(hp->heap[v / 2]), &(hp->heap[v]));
        v /= 2;
    }
}

void siftDown(my_heap* hp, int v)
{
    while(v <= hp->sz)
    {
        long long minValue = hp->heap[v];
        int child = v;
        if(v * 2 <= hp->sz && minValue > hp->heap[v * 2]) // left
        {
            minValue = hp->heap[v * 2];
            child = v * 2;
        }
        if(v * 2 + 1 <= hp->sz && minValue > hp->heap[v * 2 + 1]) // right
        {
            minValue = hp->heap[v * 2 + 1];
            child = v * 2 + 1;
        }
        if(child == v)
            break;
        swap(&(hp->heap[v]), &(hp->heap[child]));
        v = child;
    }
}

void insert(my_heap* hp, long long value)
{
    hp->sz++;
    hp->heap[hp->sz] = value;
    siftUp(hp, hp->sz);
}

long long get_min(my_heap* hp)
{
    long long ans = hp->heap[1];
    return ans;
}

void erase_min(my_heap* hp)
{
    swap(&(hp->heap[1]), &(hp->heap[hp->sz]));
    hp->sz--;
    siftDown(hp, 1);
}

int min(int a, int b)
{
    if(a < b)
        return a;

    return b;
}

void solve(int n, int k)
{
    my_heap* hp = create_heap(k);

    for(int i = 0; i < n; i++)
    {
        long long x;
        scanf("%lld", &x);
        insert(hp, x);
        if(hp->sz > k)
        {
            erase_min(hp);
        }
    }

    long long* answer = malloc(sizeof(long long) * k);
    int size = 0;
    while(hp->sz > 0)
    {
        answer[size++] = get_min(hp);
        erase_min(hp);
    }

    for(int i = size - 1; i >= 0; i--)
    {
        printf("%lld\n", answer[i]);
    }

    delete_heap(hp);
    free(answer);
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    solve(n, k);
    return 0;
}