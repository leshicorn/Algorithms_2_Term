import random

with open('input.txt', 'w') as f:

    n = int(input())
    print(n, file=f)
    for i in range(n):
        print(random.randint(0,1000000000), random.randint(0, 1000000000), file=f)