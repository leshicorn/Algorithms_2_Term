#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pair
{
    char type;
    int num;
} pair;

int check(int** arr, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        int sum = 0;

        for (int j = 0; j < m; j++)
        {
            sum += arr[i][j];
        }

        if(sum < 0)
        {
            return 0;
        }
    }

    for (int j = 0; j < m; j++)
    {
        int sum = 0;

        for (int i = 0; i < n; i++)
        {
            sum += arr[i][j];
        }

        if(sum < 0)
        {
            return 0;
        }
    }
    return 1;
}

void doRow(int** arr, int n, int m, pair* ans, int* sz, int pos)
{
    ans[*sz].type = 'l';
    ans[*sz].num = pos;
    (*sz)++;

    for (int i = 0; i < m; i++)
    {
        arr[pos][i] *= -1;
    }
}

void doCol(int** arr, int n, int m, pair* ans, int* sz, int pos)
{
    ans[*sz].type = 'c';
    ans[*sz].num = pos;
    (*sz)++;
    for (int i = 0; i < n; i++)
    {
        arr[i][pos] *= -1;
    }
}

void solve()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int** arr = (int**) malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = (int*) malloc(sizeof(int) * m);
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    pair* ans = (pair*) malloc (sizeof(pair) * (n + m));
    int size = 0;
    while(!check(arr, n, m))
    {
        for (int i = 0; i < n; i++)
        {
            int sum = 0;
            for (int j = 0; j < m; j++)
            {
                sum += arr[i][j];
            }
            if(sum < 0)
            {
                doRow(arr, n, m, ans, &size, i);
            }
        }

        for (int j = 0; j < m; j++)
        {
            int sum = 0;
            for (int i = 0; i < n; i++)
            {
                sum += arr[i][j];
            }
            if(sum < 0)
            {
                doCol(arr, n, m, ans, &size, j);
            }
        }

    }

    for (int i = 0; i < size; i++)
    {
        printf("%c %d\n", ans[i].type, ans[i].num);
    }

    for (int i = 0; i < n; i++)
    {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
    free(ans);
}


int main()
{
    solve();
    return 0;


}