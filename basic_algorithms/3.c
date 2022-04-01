#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    scanf("%d", &n);
    int* mas = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &mas[i]);
    }
    
    int sum = 0;

    for (int i = 0; i < n; i++)
    {
        if (mas[i] > sum + 1)
        {
            printf("%d\n", sum + 1);
            return 0;
        }
        sum += mas[i];
    }

    printf("%d\n", sum + 1);

    free(mas);
    return 0;
}