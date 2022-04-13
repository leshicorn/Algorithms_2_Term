#include <stdio.h>
#include <assert.h>

void solve(int p, int q)
{
    int number = 2;

    while (p != 0)
    {
        p *= number;

        if (p % q != 0)
            printf("%d ", p / q);
        else
            printf("%d\n", p / q);
        p = p % q;
        number++;
    }
    return;
}

int main()
{
    int p = 0, q = 0;
    scanf("%d %d", &p, &q);

    assert (p >= 1 && p <= q && q < 1000);

    solve(p, q);
}