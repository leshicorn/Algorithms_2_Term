with open('tests.txt', 'w') as f:
    for i in range (1000):
        print('ADD', 'Name' + str(i), str(i * i + 1), file=f)
        print('PRINT', 'Name' + str(i), file=f)
        print('EDITPHONE', 'Name' + str(i), str(i * i + 2), file=f)
        print('PRINT', 'Name' + str(i), file=f)
        print('DELETE', 'Name' + str(i), file=f)
        print('PRINT', 'Name' + str(i), file=f)