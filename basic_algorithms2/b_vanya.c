// На вход подаются числа P и Q - дробь вида P/Q
// Вывести последовательность представителей дроби в факториальной системе счисления, начиная с x/2!

#include <stdio.h>
#include <assert.h>

int main()
{
    long long int P = 0, Q = 0;
    scanf("%lld", &P);
    scanf("%lld", &Q);
    
    assert(1 <= P && P < Q && Q < 1000);

    int i = 2;

    while (P > 0)
    {
        P *= i;

        if (i > 2)
            printf(" ");
        printf("%lld", P/Q);   
        P %= Q;
        i++;
    }

    printf("\n");
    return 0;
}