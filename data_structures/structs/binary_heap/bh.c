#include <stdio.h>
#include <stdlib.h>

typedef struct my_heap{
    long long* heap;
    int sz;
} my_heap;

typedef struct massiv{
    my_heap* elem;
} massiv;

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

int main()
{
    int n = 0;
    scanf("%d", &n);
    massiv* arr = malloc(sizeof(massiv) * n);

    while (1)
    {
        int what_to_do = 0;
        scanf("%d", &what_to_do);
        switch (what_to_do)
        {
            case 0:
            {
                int number = 0, size = 0, type = 0;
                scanf("%d %d %d", &number, &size, &type);
                arr[number].elem = create_heap(size);
                //чото с типом
                break;
            }
            case 1:
            {
                int number, elem;
                scanf("%d %d", &number, &elem);
                insert(arr[number].elem, elem);
                break;
            }
            case 2:
            {
                int number;
                scanf("%d", &number);
                printf("%lld\n", get_min(arr[number].elem));
                break;
            }
            case 3:
            {
                int number;
                scanf("%d", &number);
                erase_min(arr[number].elem);
                break;
            }
            case 4:
            {
                int number;
                scanf("%d", &number);
                printf("%d\n", (arr[number].elem)->sz);
                break;
            }
            case 5:
            {
                break;
            }
            case 6:
            {
                int number;
                scanf("%d", &number);
                delete_heap(arr[number].elem);
                break;
            }
            default:
            {
                printf("End\n");
                return 0;
            }
        }
    }
}