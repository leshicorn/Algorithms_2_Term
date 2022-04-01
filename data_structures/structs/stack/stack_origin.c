#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct stack
{
    void * data;      // массив данных
    
    size_t size;      // настоящий размер
    size_t capacity;  // сколько выделено

    size_t elem_size; // размер элемента
};

struct stack * stack_new(size_t elem_size);
int stack_push(struct stack * st, const void * elem);
int stack_pop(struct stack * st, void * elem);
int stack_top(struct stack * st, void * elem);
int stack_empty(struct stack const * st);
struct stack * stack_delete(struct stack * st);
void stack_print(struct stack const * st, void (*pf) (void const * st));

struct stack * stack_new(size_t elem_size)
{
    assert(elem_size);

    struct stack * stack = (struct stack *) calloc(1, sizeof(struct stack));
    
    stack -> data = (void *) calloc(1, elem_size * sizeof(char));
    stack -> size = 0;
    stack -> capacity = 1;

    stack -> elem_size = elem_size;

    return stack;
}

int stack_push(struct stack * st, const void * elem)
{
    assert(st);
    assert(elem);
    
    if(st -> size == st -> capacity)
    {
        st -> capacity *= 2;
        st -> data = realloc(st -> data, (st -> capacity) * (st -> elem_size));
    }
    
    memcpy(st -> data + ((st -> size) * (st -> elem_size)), elem, st -> elem_size);
    
    st -> size = st -> size + 1;

    return 0;
}

int stack_pop(struct stack * st, void * elem)
{
    assert(st);
    assert(elem);

    if(st -> size != 0)
    {
        memcpy(elem, st -> data + (st -> size - 1) * (st -> elem_size), st -> elem_size);

        st -> size--;
        
        return 0;
    }
    
    return 1;
}

int stack_top(struct stack * st, void * elem)
{
    assert(st);
    assert(elem);

    if(st -> size != 0)
    {
        memcpy(elem, (st -> data) + (st -> size - 1) * (st -> elem_size), st -> elem_size);
   
        return 0;
    }

    return 1;
}

int stack_empty(struct stack const * st)
{
    assert(st);

    if(st == NULL)
    {
        return 1;
    }

    if(st -> size == 0)
    {
        return 1;
    }

    return 0;
}

struct stack * stack_delete(struct stack * st)
{
    assert(st);

    free(st -> data);
    free(st);

    return NULL;
}

void stack_print(struct stack const * st, void (*pf) (void const * st))
{
    assert(st);

    printf("[");

    for(int i = 0; i != st -> size; i++)
    {
        pf(st -> data + st -> elem_size * i);

        if(i != st -> size - 1)
        {
            printf(", ");
        }
    }

    printf("]\n");
}

static void print_double(void const *st) {
   printf("%lf", *(double *)st);
}

int main() {
    struct stack *st = stack_new(sizeof (double));
    for (int i = 0; i < 10; i++) {
        double tmp = i * i;
        stack_push(st, &tmp);
    }
    stack_print(st, print_double);
    st = stack_delete(st);
}