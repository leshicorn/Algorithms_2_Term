#include <stdio.h>
#include <stdlib.h>

int can_be_lowered(int *mas, int n, int p, int q, int hits) 
{
    p -= q;
    q *= hits;
    int remained = 0;

    for (int i = 0; i < n && hits >= 0; i++) 
    {
        remained = mas[i] - q;
        if (remained > 0) 
        {
            hits -= (remained + p - 1) / p;
        }
    }
    
    return hits >= 0;
}

int find_punches(int *mas, int n, int p, int q, int max) 
{
    int left = 1, right = max;
    int mean = 0;
    while (right > left) 
    {
        mean = (left + right) >> 1;
        if (can_be_lowered(mas, n, p, q, mean)) 
        {
            right = mean;
        } 
        else 
        {
            left = mean + 1;
        }
    }
    return left;
}

int main() 
{
    int n = 0;
    int p = 0, q = 0, max = 0;
    scanf("%d %d %d", &n, &p, &q);
    
    int *mas = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &mas[i]);
        if (mas[i] > max) {
            max = mas[i];
        }
    }

    max = (max + q - 1) / q;

    printf("%d\n", find_punches(mas, n, p, q, max));

    return 0;
}