#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

    int res = strcmp(str1, str2);
    free(str1);
    free(str2);

    return (res < 0) ? 1 : 0;
}

void sort_by_first_symbol(strings* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
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
    //FILE* fp;
    strings* arr = malloc(sizeof(strings) * 101);
    //char* str = malloc(sizeof(char) * 101);
    for (int i = 0; i < 101; i++)
    {
        arr[i].str = malloc(sizeof(char) * 101);
    }

    //if (!(fp = fopen("in.txt", "r")))
    //{
    //    return 0;  
    //}
    
   // while (!feof(fp))
    int amount_of_lines = 0;
    int n = scanf("%ms", &arr[amount_of_lines].str);
    while (n == 1)
    {
        amount_of_lines++;
        n = scanf("%ms", &arr[amount_of_lines].str);
    }

    sort_by_first_symbol(arr, amount_of_lines);

    //FILE* res;
    //res = fopen("out.txt", "w");
    //printf("\n\nResult:\n");
    for (int i = 0; i < amount_of_lines; i++)
    {
        printf("%s", arr[i].str);
    }
    printf("\n");
    //fclose(res);
    //fclose(fp);

    for (int i = 0; i < 100; i++)
    {
        free(arr[i].str);
    }
    free(arr);
}