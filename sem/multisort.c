#include <stdio.h>
#include <stdlib.h>


typedef struct data
{
    char* name;
    int * arr;
} data;

void swap(data *a, data *b)
{   
    data swaper;
    swaper.name = a->name;
    swaper.arr = a->arr;

    a->arr = b->arr;
    a->name = b->name;
    b->arr = swaper.arr;
    b->name = swaper.name;
}

void ft_sort_bubble (int *mas, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int k = 0; k < size - i - 1; k++)
        {
            
        }
    }
    return;
}

int main()
{
    int n = 0, k = 0;
    scanf("%d %d", &n, &k);
    int * priority = malloc(k * sizeof(int));
    data* mas = malloc(n * sizeof(data));

    for (int i = 0; i < k; i++)
    {
        scanf("%d", &priority[i]);
    }

    
    for (int i = 0; i < n; i++)
    {
        mas[i].name = malloc(100 * sizeof(data));
        mas[i].arr = malloc(k * sizeof(int));
        scanf("%s", mas[i].name);
        for (int j = 0; j < k; j++)
        {
            scanf("%d", &mas[i].arr[j]);
        }
    }

    //printf("\nPriority: ");
    //for (int i = 0; i < k; i++)
    //{
    //    printf("%d ", priority[i] - 1);
    //}
    //printf("\n");

    int arg_to_sort = 0;

    for (int q = 0; q < k; q++)
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - 2; j++)
            {
                if (mas[j].arr[priority[arg_to_sort] - 1] < mas[j + 1].arr[priority[arg_to_sort] - 1])
                    swap(&mas[j + 1], &mas[j]);
            }
        }
        arg_to_sort++;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%s\n", mas[i].name);
    }

    for (int i = 0; i < n; i++)
    {
        free(mas[i].name);
        free(mas[i].arr);
    }
    free(priority);
    free(mas);

    return 0;
}