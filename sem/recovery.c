#include <stdio.h>
#include <stdlib.h>

int main()
{
    int amount_of_perest = 0;
    scanf("%d", &amount_of_perest);
    int* inversion_table = malloc(sizeof(int) * amount_of_perest);

    for (int i = 0; i < amount_of_perest; i++)
    {
        scanf("%d", &inversion_table[i]);
    }

    int* result_array = malloc(sizeof(int) * amount_of_perest);
    int* flag_array = malloc(sizeof(int) * amount_of_perest);
    for (int i = 0; i < amount_of_perest; i++)
        flag_array[i] = 1;

    for (int i = amount_of_perest - 1; i >= 0; i--)
    {
        int j = 0;
        int m = amount_of_perest - 1;
        while (j < inversion_table[i] || !flag_array[m])
        {
            if (flag_array[m])
                ++j;
            --m;
        }
        result_array[i] = m + 1;
        flag_array[m] = 0;
    }

    int impossible_flag = 0;

    for (int i = 0; i < amount_of_perest; i++)
    {
        if (result_array[i] < 0)
            impossible_flag++;
    }

    if (impossible_flag != 0)
    {
        printf("IMPOSSIBLE\n");
        return 0;
    }
    
    for (int i = 0; i < amount_of_perest; i++)
    {
        printf("%d ", result_array[i]);
    }

    free(result_array);
    free(flag_array);
    free(inversion_table);

    return 0;
}