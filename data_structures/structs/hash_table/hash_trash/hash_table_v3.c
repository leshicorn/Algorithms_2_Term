#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mod 999983
#define mnoj 20029
#define MAX_STR_LEN 31
#define MAX_AMOUNT_OF_TABLES 10

typedef struct list
{
    char* key;
    char* value;
    struct list* next;
} list;

typedef struct hash_arr
{
    list** table;
} hash_arr;

/**
 * @brief Хэш функция, которая считает хэш строки "биномиально". 
 * Т.е. хэш вида (S0 * p^(n-1) + ... + S(n-1)*p^0) % mod, 
 * где p - простое число больше алфавита, а НОД(p, mod) = 1
 * 
 * @param key ключ (строка)
 * @return результат работы алгоритма ☺
 */
int hash_func(char* key);

/**
 * @brief Create a table object
 * 
 * @return list** 
 */
list** create_table();

/**
 * @brief Вставляет элемент в хэш таблицу по ключу
 * 
 * @param table таблица
 * @param key ключ
 * @param value значение
 */
void insert(list** table, char* key, char* value);

/**
 * @brief Функция находит элемент по ключу. Если не находит - вывод "MISSING"
 * 
 * @param table таблица 
 * @param key ключ
 */
void find(list** table, char* key);

/**
 * @brief Удаляет запись по ключу из хэш таблицы
 * 
 * @param table таблица
 * @param key ключ
 */
void erase(list** table, char* key);

/**
 * @brief Уничтожает хэш таблицу освобождая память
 * 
 * @param table таблица
 * @return (list** )NULL
 */
list** destroy(list** table);

int hash_func(char* key)
{
    int res = 0;
    int p = 1;  
    int strl = (int)strlen(key);

    for (int i = 0; i < strl; i++)
    {
        res = (res + key[strl - i - 1] * p) % mod;
        p *= mnoj;
    }
    res = res % mod;

    return (res > 0) ? res : mod + res;
}

list** create_table()
{
    return calloc(mod, sizeof(list*));
}

void insert(list** table, char* key, char* value)
{
    if (table == NULL)
    {
        return;
    }

    int hash = hash_func(key);

    if (table[hash] == NULL)
    {
        table[hash] = malloc(sizeof(list));
        table[hash]->key = malloc(sizeof(char) * MAX_STR_LEN);
        table[hash]->value = malloc(sizeof(char) * MAX_STR_LEN);
        table[hash]->key = strcpy(table[hash]->key, key);
        table[hash]->value = strcpy(table[hash]->value, value);
        table[hash]->next = NULL;
    }
    else
    {
        table[hash]->key = malloc(sizeof(char) * MAX_STR_LEN);
        table[hash]->value = malloc(sizeof(char) * MAX_STR_LEN);
        table[hash]->key = strcpy(table[hash]->key, key);
        table[hash]->value = strcpy(table[hash]->value, value);
        table[hash]->next = NULL;
    }
}

void find(list** table, char* key)
{
    if (table == NULL)
    {
        printf("MISSING\n");
        return;
    }
    int hash = hash_func(key);
    list* cur = table[hash];

    if (cur == NULL || cur->key == NULL || cur->value == NULL)
    {
        printf("MISSING\n");
        return;
    }

    if (strcmp(cur->key, key) == 0)
    {
        printf("%s\n", cur->value);
        return;
    }

    // if (strcmp(cur->key, key) != 0)
    // {
        // while (cur->key != NULL)
            // cur = cur->next;
        // if (strcmp(cur->key, key) == 0)
        // {
            // printf("%s\n", cur->value);
            // return;
        // }
        // else
            // printf("MISSING\n");
    // }
    return;

}

void erase(list** table, char* key)
{
    if (table == NULL)
        return;
    int hash = hash_func(key);
    list* cur = table[hash];

    if (cur == NULL || cur->key == NULL || cur->value == NULL)
    {
        return;
    }
    if (strcmp(cur->key, key) == 0)
    {
        free(cur->key);
        free(cur->value);
        free(cur->next);
        cur->next = NULL;
        free(cur);
    }
}

list** destroy(list** table)
{
    if (table == NULL)
        return NULL;
    for (int i = 0; i < mod; i++)
    {
        list* cur = table[i];
        if (cur != NULL)
        {
            if (cur->key != NULL)
                free(cur->key);
            if (cur->value != NULL)
                free(cur->value);
        }
    }
    free(table);
    
    return NULL;
}

int main()
{
    freopen("input.txt", "r", stdin);

    hash_arr* array = calloc(MAX_AMOUNT_OF_TABLES, sizeof(hash_arr));
    int* used_tables = calloc(MAX_AMOUNT_OF_TABLES, sizeof(int));
    int amo_of_tables = 0;

    char* command = calloc(MAX_STR_LEN, sizeof(char));
    char* value = calloc(MAX_STR_LEN, sizeof(char));
    char* key = calloc(MAX_STR_LEN, sizeof(char));
    int cur_table_number = -1;

    while (scanf("%s", command) != EOF)
    {
        if (command[0] == 'c')
        {
            scanf("%d", &cur_table_number);
            array[cur_table_number].table = create_table();
            used_tables[amo_of_tables++] = cur_table_number;
        }
        if (command[0] == 'i')
        {
            scanf("%d %s %s", &cur_table_number, key, value);
            insert(array[cur_table_number].table, key, value);
        }
        if (command[0] == 'e')
        {
            scanf("%d %s", &cur_table_number, key);
            erase(array[cur_table_number].table, key);
        }
        if (command[0] == 'f')
        {
            scanf("%d %s", &cur_table_number, key);
            find(array[cur_table_number].table, key);
        }
        if (command[0] == 'd')
        {
            scanf("%d", &cur_table_number);
            array[cur_table_number].table = destroy(array[cur_table_number].table);

        }
    }

    free(array);
    free(command);
    free(value);
    free(key);
}