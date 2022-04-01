#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fast_sort(unsigned *begin, unsigned *end)
{
    unsigned max = 0;
    unsigned* begin_c = begin;
    while (begin_c != end)
    {
        if (*begin_c > max)
            max = *begin_c;
        ++begin_c;
    }
    
    unsigned n = end - begin;
    unsigned size = (max + 1) * (n + 1) * sizeof(unsigned);
    unsigned* help_array = malloc(size);

    unsigned* help_array_c = help_array;
    unsigned n_copy = n;
    while (n_copy--)
    {
        *help_array_c = 0;
        ++help_array_c;
    }
    //memset(help_array, 0, (end - begin) * (max + 1));

    for (unsigned i = 0; i < n; ++i)
    {
        ++help_array[*(begin + i)];
    }
        
    unsigned flag = 0;
    for (unsigned i = 0; i < max + 1; ++i)
    {
        for (unsigned j = 0; j < help_array[i]; ++j)
        {
            begin[flag++] = i;
        }
    }
    free(help_array);
}

int main()
{
    unsigned size = 10;
    unsigned* array = malloc(sizeof(unsigned) * size);
    
    for (unsigned i = 0; i < size; i++)
    {
        array[i] = rand() % (rand() % size + 1);//size - i;
    }

    for (unsigned i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n\n\n");

    fast_sort(array, array + size);
    
    for (unsigned i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
}