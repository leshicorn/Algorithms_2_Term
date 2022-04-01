#include <stdio.h>
#include <stdlib.h>

#define MAXN 86401

int max(int first, int second)
{
    return (first > second) ? first : second;
}

void solve()
{
    int n;
    scanf("%d", &n);
    int* times = (int*)malloc(sizeof(int) * 100000);

    for (int i = 0; i < 100000; i++)
    {
        times[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        int startH, startM, startS;
        int finishH, finishM, finishS;
        scanf("%d:%d:%d %d:%d:%d", &startH, &startM, &startS, &finishH, &finishM, &finishS);
        int l = startH * 3600 + startM * 60 + startS;
        int r = finishH * 3600 + finishM * 60 + finishS;
        times[l]++;
        times[r + 1]--;
    }

    int ans = 0;
    int sum = 0;

    for (int i = 0; i < MAXN; i++)
    {
        sum += times[i];
        ans = max(ans, sum);
    }

    printf("%d", ans);
    free(times);
}

int main()
{
    solve();
    return 0;
}