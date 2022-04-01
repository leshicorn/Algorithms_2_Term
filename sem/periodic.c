#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* fractionToDecimal(long int a, long int b)
{
    if (a == 0) return "0";
    char* res = (char*)malloc(sizeof(char) * 101);
    a = abs(a);
    b = abs(b);
    
    sprintf(res, "%.54lf", (double)a / (double)b);

    if (a % b == 0) return res;

    strcat(res, ".");

    long int rem = a % b;

    

    printf("%s", res);
    return res;
}

int main()
{
    double n = 0, m = 0;
    scanf("%lf %lf", &n, &m);

    fractionToDecimal(n, m);

    //printf("%lf", n / m);
    return 0;
}