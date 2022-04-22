#include <stdio.h>
#include <stdlib.h>

int check(int cou, int* arr, int* new_arr, int n, int p, int q)
{
	int size = 0;
	for (int i = 0; i < n; i++)
	{
		if (1LL * arr[i] - 1LL * cou * q > 0)
		{
			new_arr[size++] = arr[i] - cou * q;
		}
	}
	
	if (size == 0)
		return 1;
	if (size > 0 && p == q)
		return 0;
	
	long long rtm = 0;
	int delta = p - q;

	for (int i = 0; i < size; i++)
	{
		rtm += 1LL * (new_arr[i] + delta - 1) / delta;
	}
	
	return (rtm <= cou) ? 1 : 0;
}

int solve(int* arr, int n, int p, int q)
{
	int* new_arr = (int*) malloc(sizeof(int) * n);

	int left = 0, right = 1000000000;

	while(left + 1 < right)
	{
		int mid = (left + right) / 2;
		
		if (check(mid, arr, new_arr, n, p, q))
		{
			right = mid;
		}
		else
		{
			left = mid;
		}
	}
	
	free(new_arr);
	return right;
}

int main()
{
	int n = 0, p = 0, q = 0;
	scanf("%d%d%d", &n, &p, &q);

	int* arr = (int*) malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	printf("%d\n", solve(arr, n, p, q));
	
	free(arr);	
	return 0;
}