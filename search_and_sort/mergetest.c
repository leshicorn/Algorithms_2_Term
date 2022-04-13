#include <stdio.h>
#include <stdlib.h>

int* merge(int* arr1, int* arr2, int size)
{
    int* res = malloc(sizeof(int) * size * 2);
    int ind = 0;
    int *end1 = arr1 + size, *end2 = arr2 + size;

    while (arr1 != end1 && arr2 != end2)
    {
        int min;
        int res_cur;
        if (*arr1 < *arr2 && arr1 != end1 && arr2 != end2)
        {
            min = *arr1;
            res[ind] = *arr1;
            res_cur = res[ind];
            ++arr1;
            ind++;
        }
        else if (*arr2 < *arr1 && arr1 != end1 && arr2 != end2)
        {
            min = *arr2;
            res[ind] = *arr2;
            res_cur = res[ind];
            ++arr2;
            ind++;
        }
        if (arr1 == end1)
        {
            min = *arr2;
            res[ind] = *arr2;
            res_cur = res[ind];
            ++arr2;
            ++ind;
        }
        else if (arr2 == end2)
        {
            min = *arr1;
            res[ind] = *arr1;
            res_cur = res[ind];
            ++arr1;
            ++ind;
        }
    }
    return res;
}

int main()
{
    int size = 5;

    int* arr1 = malloc(sizeof(int) * size);
    int* arr2 = malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr1[i]);
    }
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr2[i]);
    }

    int* res = merge(arr1, arr2, size);
    for (int i = 0; i < size * 2; i++)
    {
        printf("%d ", res[i]);
    }
}