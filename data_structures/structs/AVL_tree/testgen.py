import random
import time

seconds = time.time()

with open('input.txt', 'w') as f:
    for i in range(1000000000):
        delta = time.time()
        if delta - seconds >= 60:
            break
        command = random.randint(1, 3)
        if command == 1:
            print('insert', 'NAME' + str(random.randint(0, 9)), 'NAME' + str(random.randint(0, 9) * random.randint(0, 9)), file=f)
        if command == 2:
            print('erase', 'NAME' + str(random.randint(0, 9)), file=f)
        if command == 3:
            print('find', 'NAME' + str(random.randint(0, 9)), file=f)
