#include <stdio.h>
#include <stdlib.h>

#define SIZEOFARR 9

int min(int a, int b, int* number)
{
    return a < b ? a : b;
}

void print_arr(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* merge(int* arr1, int* arr2, int size)
{
    int* res = malloc(sizeof(int) * (size * 2 + 1));
    int* end1 = arr1 + size, *end2 = arr2 + size;
    int ind = 0;

    while (arr1 != end1 && arr2 != end2)
    {
        if (*arr1 <= *arr2 && arr1 != end1 && arr2 != end2)
        {
            res[ind] = *arr1;
            ++arr1;
            ++ind;
        }
        else if (*arr2 < *arr1 && arr1 != end1 && arr2 != end2)
        {
            res[ind] = *arr2;
            ++arr2;
            ++ind;
        }
        if (arr1 == end1 && arr2 != end2)
        {
            res[ind] = *arr2;
            ++arr2;
            ++ind;
        }
        else
        {
            res[ind] = *arr1;
            ++arr1;
            ++ind;
        }
    }
    return res;
}

int main()
{
    
}