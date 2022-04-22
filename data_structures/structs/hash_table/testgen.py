import random

with open('input.txt', 'w') as f:
    for i in range (10):
        print('create', i, file=f)
    for i in range(100):
        command = random.randint(1, 5)
        if command == 1:
            print('insert', random.randint(0, 9), 'NAME' + str(random.randint(0, 9)), 'NAME' + str(random.randint(0, 9) * random.randint(0, 9)), file=f)
        if command == 2:
            print('erase', random.randint(0, 9), 'NAME' + str(random.randint(0, 9)), file=f)
        if command == 3 or 4:
            print('find', random.randint(0, 9), 'NAME' + str(random.randint(0, 9)), file=f)
        if command == 5:
            print('destroy', random.randint(0, 9), file=f)
        command = random.randint(0, 9)
        if command == 0:
            print('create', random.randint(0, 9), file=f)
