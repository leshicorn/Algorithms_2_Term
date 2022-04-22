#include <stdio.h>
#include <stdlib.h>

/*def quickselect_median(l, pivot_fn=random.choice):
    if len(l) % 2 == 1:
        return quickselect(l, len(l) / 2, pivot_fn)
    else:
        return 0.5 * (quickselect(l, len(l) / 2 - 1, pivot_fn) +
                      quickselect(l, len(l) / 2, pivot_fn))*/

int quickselect_median(int* arr, int arr_len, int rand_pivot)
{
    if (arr_len % 2 == 1)
        return quickselect(arr, arr_len / 2 - 1, rand_pivot);
    else
        return 0.5 * quickselect(arr, arr_len / 2 - 1, rand_pivot) + quickselect(arr, arr_len / 2, rand_pivot);
}

int quickselect(int* arr, int arr_len, int pivot_fn)
{
    
}

int main()
{

}