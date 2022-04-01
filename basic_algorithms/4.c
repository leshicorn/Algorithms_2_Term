#include <stdio.h>
#include <stdlib.h>

void rec(char first_symbol, int left, int right, int start_left_index, int start_right_index)
{
    if (left == right)
    {
        if (start_left_index <= left && left <= start_right_index)
        {
            printf("%c",first_symbol);
        }
        return;
    }
    if (start_left_index <= left && left <= start_right_index)
    {
        printf("%c", first_symbol);
    }
    
    int mid = (left + right) / 2;
    
    rec(first_symbol - 1, left + 1, mid, start_left_index, start_right_index);
    rec(first_symbol - 1, mid + 1, right, start_left_index, start_right_index);
}

int main()
{
    int n = 0, left = 0, right = 0;
    scanf("%d %d %d", &n, &left, &right);
    int len = (1 << n) - 1;

    char first_symbol = ('a' + n - 1);
    rec(first_symbol, 0, len - 1, left - 1, right - 1);
    return 0;
}