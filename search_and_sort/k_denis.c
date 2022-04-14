#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int check(int* arr, int n, int m, int k)
{
 int sum = 0;
 for(int i = 0; i < n; i++)
 {
  if(sum + arr[i] > m)
  {
   k--;
   sum = arr[i];
   if(k <= 0)
    return 0;
  }
  else
  {
   sum += arr[i];
  }
 }

 return sum <= m && k > 0;
}

int main()
{
 int k, n;
 scanf("%d %d", &k, &n);
 int* arr = (int*) malloc(sizeof(int) * n);

 for(int i = 0; i < n; i++)
 {
  scanf("%d", &arr[i]);
 }


 int l = 0;
 int r = 1000000;

 while(l < r)
 {
  int mid = (l + r) / 2;
  if(check(arr, n, mid, k))
   r = mid;
  else
   l = mid + 1;
 }

 printf("%d", l);

 free(arr);
 arr = NULL;
 return 0;
}