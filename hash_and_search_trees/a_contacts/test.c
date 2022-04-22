#include <stdio.h>
#include <stdlib.h>

#define MAX_STR_LEN 31

int main()
{
    char* phone_number = malloc(sizeof(char) * MAX_STR_LEN);
    char* arg1 = malloc(sizeof(char) * MAX_STR_LEN);
    char* arg2 = malloc(sizeof(char) * MAX_STR_LEN);

    int n = scanf("%s %s %s", phone_number, arg1, arg2);
    printf("%d\n", n);
}