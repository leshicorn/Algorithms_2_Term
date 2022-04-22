#include <stdio.h>
#include <stdlib.h>

int check(int* arr, int n, int m, int k)
{
    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (sum + arr[i] > m)
        {
            k--;
            sum = arr[i];
            if (k <= 0)
            {
                return 0;
            }
        }
        else
        {
            sum += arr[i];
        }
    }
    return (sum <= m && k > 0);
}

int main()
{
    int k = 0, n = 0;
    scanf("%d%d", &k, &n);
    int* arr = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int left = 0, right = 1000000;

    while (left < right)
    {
        int mid = (left + right) / 2;
        if (check(arr, n, mid, k))
            right = mid;
        else
            left = mid + 1;
    }
    printf("%d\n", left);
    free(arr);
    return 0;
}