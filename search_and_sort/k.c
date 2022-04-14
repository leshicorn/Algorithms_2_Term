#include <stdio.h>
#include <stdlib.h>

int solve(int* arr, int n, int m, int k)
{
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        if(sum + arr[i] > m)
        {
            k--;
            sum = arr[i];
            if(k <= 0)
                return 0;
        }
        else
        {
            sum += arr[i];
        }
    }
    if (sum <= m && k > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int n = 0, k = 0;
    scanf("%d %d", &k, &n);
    int* v = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
    }

    int start = 0;
    int finish = 1000000;

    while(start < finish)
    {
        int mid = (start + finish) / 2;
        if(solve(v, n, mid, k) == 1)
        {
            finish = mid;
        }
        else
        {
            start = mid + 1;
        }
    }

    printf("%d\n", start);
    return 0;
}