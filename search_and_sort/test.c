#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main()
{
    printf("%d", atoi("0987"));
}