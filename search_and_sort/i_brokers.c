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

int main()
{
	int n;
	scanf("%d", &n);
	my_heap* myHeap = create_heap(n * 4);

	for(int i = 0; i < n; i++)
	{
		long long x;
		scanf("%lld", &x);
		insert(myHeap, x);
	}

	double ans = 0;

	while(myHeap->sz > 1)
	{
		long long min1 = get_min(myHeap);
		erase_min(myHeap);

		long long min2 = get_min(myHeap);
		erase_min(myHeap);
        
		ans += (double)(min1 + min2) * 0.01;
		insert(myHeap, min1 + min2);
	}

	printf("%.2f\n", ans);

	delete_heap(myHeap);
	return 0;
}