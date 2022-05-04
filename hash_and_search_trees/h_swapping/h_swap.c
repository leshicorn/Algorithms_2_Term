#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000000000

typedef struct tipa_hash
{
    int value;
    int pos;
} hash;

typedef struct pair
{
    int value;
    int pos;
} pair;

int swap(pair* a, pair* b)
{
    int swaper = a->value;
    int swaper_pos = a->pos;
    a->value = b->value;
    a->pos = b->pos;
    b->value = swaper;
    b->pos = swaper_pos;

    return abs(b->pos - a->pos);
}

int main()
{
    hash* arr = calloc(SIZE, sizeof(hash));
    
}

/*int main()
{
    int n = 0;
    scanf("%d", &n);
    pair* arr = malloc(sizeof(pair) * 1);
    int flag = 0;
    

    for (int i = 0; i < n; i++)
    {
        int sw1 = 0, sw2 = 0;
        scanf("%d %d", &sw1, &sw2);
        
        int distance = swap(&arr[sw1], &arr[sw2]);
    }

    free(arr);
}*/