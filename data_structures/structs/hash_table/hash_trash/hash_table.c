#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define mod 1033
#define mnoj 53
#define hash_size 100000
#define str_len 200

typedef struct hash_table
{
    
    char* data;
} hash_table;

typedef struct hash_arr
{
    hash_table* elem;
} hash_arr;

int charcmp(char s1, char s2)
{
    return (s1 == s2) ? 0 : 1;
}

char** split(char* str)
{
    char ** res = (char**)malloc(sizeof(char) * 32);
    int i = 0, j = 0;
    for (int i = 0; i < (int)strlen(str); i++)
    {
        res[i] = (char*)malloc(sizeof(char) * (int)strlen(str));
    }
    i = 0;
    if (!res)
        return NULL;
    
    while (*str)
    {
        if (charcmp(*str, ' ') != 0 && charcmp(*str, '\n') != 0)
        {
            res[i][j] = *str;
            j++;
        }
        else if (charcmp(*str, '\n') != 0)
        {
            j = 0;
            i++;
        }
        ++str;
    }
    return res;
}

int ft_strlen(char *str)
{
    int len = 0;

    while (*str++)
        ++len;

    return len;
}

/**
 * @brief Хэш функция, которая считает хэш строки "биномиально". 
 * Т.е. хэш вида (S0 * p^(n-1) + ... + S(n-1)*p^0) % mod, 
 * где p - простое число больше алфавита, а НОД(p, mod) = 1
 * 
 * @param key ключ (строка)
 * @return результат работы алгоритма ☺
 */
int hash_func(char* key)
{
    int res = 0;
    int p = 1;  
    int strlen = ft_strlen(key);

    for (int i = 0; i < strlen; i++)
    {
        res = (res + key[strlen - i - 1] * p) % mod;
        p *= mnoj;
    }
    res = res % mod;

    return (res > 0) ? res : mod + res;
}

hash_table* hash_create()
{
    hash_table* table = malloc(sizeof(hash_table) * (mod + 1));
    for (int i = 0; i < mod; i++)
    {
        table[i].data = NULL;
    }
    return table;
}

void insert(hash_table* table, char* key, char* value)
{
    if (table == NULL)
        return;
    int Key = hash_func(key);
    if (table[Key].data == NULL)
    {
        table[Key].data = malloc(sizeof(value) + sizeof(char));
        table[Key].data = strcpy(table[Key].data, value);
    }
    else
    {
        table[Key].data = malloc(sizeof(value) + sizeof(char));
        table[Key].data = strcpy(table[Key].data, value);
    }
}

void erase(hash_table* table, char* key)
{
    if (table == NULL)
        return;
    free(table[hash_func(key)].data);
    table[hash_func(key)].data = NULL;
}

void find(hash_table* table, char* key)
{    
    int Key = hash_func(key);
    if (table[Key].data != NULL)
    {
        printf("%s\n", table[Key].data);
    }
    else if ((table == NULL))
    {
        printf("MISSING\n");
    }
    else
    {
        printf("MISSING\n");
    }
}

void destroy(hash_table* table)
{
    free(table);
    table = NULL;
}

int main()
{
	hash_table **table_arr = calloc(10, sizeof(hash_table*));
	for (int i = 0; i < 10; i++)
		table_arr[i] = NULL;
	char op[20] = {0};
	while (scanf("%s", op) != EOF)
	{
		if (strcmp(op, "create") == 0)
		{
			size_t num = 0;
			scanf("%zu", &num);
			table_arr[num] = hash_create(hash_size);
		}
		else if (strcmp(op, "insert") == 0)
		{
			size_t num = 0;
			char key[str_len] = {0}, value[str_len] = {0};
			scanf("%zu %21s %21s", &num, key, value);
			if (table_arr[num] != NULL)
			{
				int hash = (int) (hash_func(key) % hash_size);
				struct list *find = list_find(table_arr[num]->arr[hash], key);
				if (find == NULL)
					table_arr[num]->arr[hash] = list_insert(table_arr[num]->arr[hash], key, value);
				else
					strcpy(find->elem.val, value);
			}
		}
		else if (strcmp(op, "erase") == 0)
		{
			size_t num = 0;
			char key[str_len] = {0};
			scanf("%zu %21s", &num, key);
			if (table_arr[num] != NULL)
			{
				int hash = (int)(hash_func(key) % hash_size);
				table_arr[num]->arr[hash] = list_erase(table_arr[num]->arr[hash], key);
			}
		}
		else if (strcmp(op, "find") == 0)
		{
			size_t num = 0;
			char key[str_len] = {0};
			scanf("%zu %21s", &num, key);
			if (table_arr[num] == NULL)
				printf("MISSING\n");
			else
			{
				int hash = (int) (hash_func(key) % hash_size);
				struct list *find = list_find(table_arr[num]->arr[hash], key);
				if (find == NULL)
					printf("MISSING\n");
				else
					printf("%s\n", find->elem.val);
			}
		}
		else if (strcmp(op, "destroy") == 0)
		{
			size_t num = 0;
			scanf("%zu", &num);
			table_arr[num] = hashtable_delete(table_arr[num]);
		}
	}
	for (int i = 0; i < 10; i++)
		table_arr[i] = hashtable_delete(table_arr[i]);
	free(table_arr);
	return 0;
}