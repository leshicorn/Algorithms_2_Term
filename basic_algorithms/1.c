#include <stdio.h>
#include <stdlib.h>

int solve(int* coins, int n)
{
	int coins_cur = 0;
	int coins_min = 0;
	int i = 0;

	for(i = 0; i < n; i++)
	{
		if(coins[i] == 5)
		{
			coins_cur++;
		}
		else
		{
			coins[i] -= 5;
			if(coins_cur >= coins[i] / 5)
			{
				coins_cur -= coins[i] / 5;
			}
			else
			{
				coins_min += (coins[i] - coins_cur * 5) / 5;
				coins_cur = 0;
			}

		}
	}
	return coins_min;
}

int main()
{
	int n;
	scanf("%d", &n);
	int* coins = malloc(sizeof(int) * (n + 1));
	int i = 0;

	for(i = 0; i < n; i++)
	{
		scanf("%d", &coins[i]);
	}

	int answer = solve(coins, n);
	printf("%d", answer);
	return 0;
}