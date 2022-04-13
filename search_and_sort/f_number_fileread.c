#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct strings
{
    char* str;
} strings;

void swap_strings(strings* a, strings* b)
{
    strings swaper = *a;
    *a = *b;
    *b = swaper;
}

void print_arr(strings* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%s\n", arr[i].str);
    }
}

char* sum_str(char* str1, char* str2)
{
    char* res = malloc(sizeof(char) * (strlen(str1) + strlen(str2) + 1));
    char* res_copy = res;

    while (*str1 != 0)
    {
        *res = *str1;
        ++str1;
        ++res;
    } 
    while (*str2 != 0)
    {
        *res = *str2;
        ++str2;
        ++res;
    }       

    return res_copy;
}

int comparator(strings* a, strings* b)
{
    char* str1 = sum_str(a->str, b->str);
    char* str2 = sum_str(b->str, a->str);

    int s1 = atoi(str1);
    int s2 = atoi(str2);

    free(str1);
    free(str2);

    return (s1 - s2 < 0) ? 1 : 0;
}

void sort_by_first_symbol(strings* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (comparator(&arr[j], &arr[j + 1]) != 0)
            {
                swap_strings(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main()
{
    FILE* fp;
    strings* arr = malloc(sizeof(strings) * 100);
    int amo_strings = 0;

    if (!(fp = fopen("in.txt", "r")))
    {
        return 0;
    }
    
    while (!feof(fp))
    {
        fscanf(fp, "%ms", &(arr[amo_strings].str));
        amo_strings++;
    }

    sort_by_first_symbol(arr, amo_strings);

    //FILE* res;
    //res = fopen("out.txt", "w");

    for (int i = 0; i < amo_strings; i++)
    {
        printf("%s", arr[i].str);
    }
    printf("\n");
    //fclose(res);
    fclose(fp);


    for (int i = 0; i < amo_strings; i++)
    {
        free(arr[i].str);
    }
    free(arr);
}