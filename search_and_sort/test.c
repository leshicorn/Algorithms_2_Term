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
    char* str1 = malloc(100);
    char* str2 = malloc(100);

    scanf("%s", str1);
    scanf("%s", str2);

    printf("%s\n", sum_str(str1, str2));
}