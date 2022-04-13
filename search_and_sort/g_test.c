#include <stdio.h>
#include <stdlib.h>

long long int count = 0;

int* copy(int* mas, int s, int f)
{
    int* result = malloc((f - s) * sizeof(int));

    for(int i = s; i < f; i++)
    {
        result[i - s] = mas[i];
    }

    return result;
}

void print(int* mas, int len)
{
    for(int i = 0; i < len; i++)
    {
        printf("%d ", mas[i]);
    }
    printf("\n");
    return;
}

void merge_and_count(int* a, int* b, int len_a, int len_b, int* mas)
{
    int liter = 0;
    int riter = 0;
    int size = len_a + len_b;
    int tmp[size];

    for(int i = 0; i < size; i++)
    {
        if(a[liter] <= b[riter])
        {
            tmp[i] = a[liter++];
            //count += len_b - riter;
        }
        else
        {
            tmp[i] = b[riter++];
            count += len_a - liter;
        }
        if (liter == len_a){
            while(riter < len_b)
            {
                tmp[++i] = b[riter++];
            }
            break;
        } 
        else if (riter == len_b)
        {
            while(liter < len_a)
            {
                tmp[++i] = a[liter++];
            }
            break;
        }
    }

    for (int i = 0; i < size; i++)
    {
        mas[i] = tmp[i];
    }
    return;
}

void sort_and_count(int* mas, int len)
{
    if (len == 1)
    {
        return;
    }
    
    int* a = copy(mas, 0, len / 2);
    int* b = copy(mas, len / 2, len);
    sort_and_count(a, len / 2);
    sort_and_count(b, len - len / 2);
    merge_and_count(a, b, len / 2, len - len / 2, mas);
}

int main()
{
    int n = 0;
    scanf("%d", &n);

    int* mas = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &mas[i]);
    }
    sort_and_count(mas, n);
    printf("%lld\n", count);
    //print(mas, n);
    return 0;
}