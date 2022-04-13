#include <stdio.h>
#include <stdlib.h>

typedef long long int lli;

lli merge_sum(int N, int *A)
{
    int index_1 = 0, index_2 = 0, elem = 0, count = 1;
    lli sum = 0;

    while (index_1 != N || index_2 != N)
    {
        if (index_1 == N)
        {
            scanf("%d", &elem);
            if ((count % 2) == 1)
            {
                sum = (sum + elem) % 1000000000;
            }
            count++;
            index_2++;
        }
        else if (index_2 == N)
        {
            if ((count % 2) == 1)
            {
                sum = (sum + A[index_1]) % 1000000000;
            }
            count++;
            index_1++;
        }
        else
        {
            scanf("%d", &elem);
            index_2++;
            while (index_1 != N)
            {
                if (A[index_1] >= elem)
                {
                    break;
                }
                if (count % 2 == 1)
                {
                    sum = (sum + A[index_1]) % 1000000000;
                }
                index_1++;
                count++;
            }
            if (count % 2 == 1)
            {
                sum = (sum + elem) % 1000000000;
            }
            count++;
        } 
    }
    return sum;
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    int *arr = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    lli sum = merge_sum(n, arr);

    printf("%lld\n", sum);

    free(arr);
    return 0;
}

/*
Сложность работы по времени O(n)
Сложность работы по памяти O(n)
*/