#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_LEN 26
#define STOCK_SIZE 1000000

typedef unsigned int type;

typedef struct symb_amount
{
    type amount;
    char symbol;
} symb;


int ft_strlen(char *str)
{
    int len = 0;

    while (*str++)
        ++len;

    return len;
}

void swap(symb* a, symb* b)
{
    symb swaper = *a;
    *a = *b;
    *b = swaper;
}

void bubble_sort(symb *arr)
{
    for (int i = 0; i < ALPHABET_LEN; i++)
    {
        for (int j = 0; j < ALPHABET_LEN - i - 1; j++)
        {
            if (arr[j].amount < arr[j + 1].amount)
                swap(&arr[j], &arr[j + 1]);
        }
    }
}

void bubble_sort_symbols(symb* arr)
{
    int i = 0;
    while (arr[i].amount == arr[i + 1].amount)
    {
        if (arr[i].symbol > arr[i + 1].symbol)
            swap(&arr[i + 1], &arr[i]);
        i++;
    }
}

void print_arr(symb* arr)
{
    for (int i = 0; i < ALPHABET_LEN; i++)
    {
        if (arr[i].amount != 0)
            printf("%c %d\n", arr[i].symbol, arr[i].amount);
    }
}

int main()
{
    char* str = malloc(sizeof(char) * STOCK_SIZE);
    
    scanf("%s", str);

    int strlen = ft_strlen(str);
    str = realloc(str, strlen);

    symb* res = malloc(sizeof(symb) * (ALPHABET_LEN + 1));
    for (int i = 0; i < ALPHABET_LEN; i++)
    {
        res[i].symbol = 'A' + i;
    }

    for (int i = 0; i < strlen; i++)
    {
        res[str[i] - 'A'].amount++;
    }

    bubble_sort(res);
    bubble_sort_symbols(res);
    print_arr(res);

    free(res);
    free(str);
}