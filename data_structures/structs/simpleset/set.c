#include <stdio.h>
#include <stdlib.h>

struct set
{
    char *data;
    size_t capacity;
};

struct set *set_new(size_t capacity)
{
    struct set *s = (struct set *) calloc(1, sizeof(struct set));

    s->data = (char *) calloc((capacity - 1) / 8 + 1, 1);
    s->capacity = capacity;
    return s;
}

int set_insert(struct set *s, size_t elem)
{
    if (elem >= s->capacity)
        return 1;
    s->data[elem / 8] |= (1 << (elem % 8));
    return 0;
}

int set_erase(struct set *s, size_t elem)
{
    if (elem >= s->capacity)
        return 1;
    s->data[elem / 8] &= ~(1 << (elem % 8));
    return 0;
}

int set_find(struct set const *s, size_t elem)
{
    if ((s->data[elem / 8] & (1 << (elem % 8))) != 0)
        return 1;
    return 0;
}

struct set *set_delete(struct set *s)
{
    free(s->data);
    free(s);
    return NULL;
}

int set_empty(struct set const *s) 
{
    for (size_t i = 0; i < s->capacity; ++i)
    {
        if (set_find(s, i) == 1)
            return 1;
    }
    return 0;
}

ssize_t set_findfirst(struct set const *s, size_t start)
{
    for (size_t i = start; i < s->capacity; ++i)
    {
        if (set_find(s, i) == 1)
            return i;
    }
    return -1;
}

size_t set_size(struct set const *s)
{
    size_t size = 0;
    for (size_t i = 0; i < s->capacity; ++i)
    {
        if (set_find(s, i) == 1)
            ++size;
    }
    return size;
}

void set_print(struct set const *s)
{
    printf("[");
    size_t size = set_size(s), j = 1;
    for (size_t i = 0; i < s->capacity; ++i)
    {
        if (set_find(s, i))
        {
            printf("%zu", i);
            if (i != s->capacity - 1 && j != size)
            {
                printf(", ");
                ++j;
            }
        }
    }
    printf("]\n");
}