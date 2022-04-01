#include <stdio.h>
#include <stdlib.h>

int sum(int var1, int var2, int mod)
{
    if (var1 + var2 >= mod) 
        return var1 + var2 - mod;
    return var1 + var2;
}

int mult(int var1, int var2, int mod)
{
    return ((long long)var1 * (long long)var2) % mod;
}

int polinome(int* coeffs, int n, int mod, int x)
{
    int res = 0;
    int multiplayer = 1;

    for (int i = n - 1; i >= 0; i--)
    {
        res = sum(res, mult(coeffs[i], multiplayer, mod), mod);
        multiplayer = mult(multiplayer, x, mod);
    }

    return res;
}

int main()
{
    int n = 0, m = 0, mod = 0;
    scanf("%d %d %d", &n, &m, &mod);
    int* coeffs = malloc(sizeof(int) * (n + 1));

    for (int i = 0; i < n + 1; i++)
    {
        scanf("%d", &coeffs[i]);
    }

    //int* res = malloc(sizeof(int) * (n + 1));

    for (int i = 0; i < m; i++)
    {
        int x = 0;
        scanf("%d", &x);
        if (i != m - 1)
            //res[i] = polinome(coeffs, n + 1, mod, x);
            printf("%d\n", polinome(coeffs, n + 1, mod, x));
        else
        {
            //res[i] = polinome(coeffs, n + 1, mod, x);
            printf("%d", polinome(coeffs, n + 1, mod, x));
        }
    }

    free(coeffs);
    return 0;
}              