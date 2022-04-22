#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mod 1033
#define mnoj 53
#define MAX_STR_LEN 31
#define MAX_COMMAND_LEN 11

/**
 * @brief Структура хэша
 * @param key Значение ключа (до хэш-функции)
 * @param data Данные, по ключу
 * @param next Указатель на 'следующий' элемент (если коллизии)
 */
typedef struct hashnode
{
    char* key;
    char* data;                       
    struct hashnode *next;
} hash;

int hash_func(char* key);
void add(hash ** table, char* phone_number, char* sur);
void delete(hash ** table, char* phone_number);
void find(hash ** table, char* phone_number);

int ft_strcmp(char* s1, char* s2)
{
    while (*s1 == *s2 && *s1 && *s2)
    {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

char* ft_strcpy(char* dest, char* src)
{
    char* dest_copy = dest;

    while(*src)
    {
        *dest = *src;
        ++src;
        ++dest;
    }
    *dest = 0;
    
    return dest_copy;
}

/**
 * @brief Добавление элемента в хэш-таблицу
 * 
 * @param table Сама хэш таблица
 * @param phone_number Номер телефона
 * @param sur Данные
 */
void add(hash ** table, char* phone_number, char* sur)
{
    int hash_key = hash_func(phone_number);
    hash *cur = table[hash_key];  
    if (table[hash_key] == NULL)
    {
        table[hash_key] = (hash*)malloc(sizeof(hash));
        table[hash_key]->key = malloc(sizeof(char) * 100);
        table[hash_key]->data = malloc(sizeof(char) * 100);
        ft_strcpy(table[hash_key]->key, phone_number);
        ft_strcpy(table[hash_key]->data, sur);
        table[hash_key]->next = NULL;
    }
    else
    {
		while (cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = (hash*)malloc(sizeof(hash));
        cur->next->key = malloc(sizeof(char) * MAX_STR_LEN);
        cur->next->data = malloc(sizeof(char) * MAX_STR_LEN);
        ft_strcpy(cur->next->key, phone_number);
		ft_strcpy(cur->next->data, sur);
		cur->next->next = NULL;
	}
}

/**
 * @brief Удаление элемента из хэш таблица
 * 
 * @param table сама таблица
 * @param name имя
 */
void delete(hash ** table, char* name)
{
    int hash_key = hash_func(name);
	hash *cur = table[hash_key];
	
    if (cur == NULL)
    {
        printf("ERROR\n");
        return;
    }

	while (cur->next != NULL && ft_strcmp(cur->next->key, name) != 0)
    {
        cur = cur->next;
    }

    if (cur->next == NULL)
    {
        printf("ERROR\n");
    }
    else if (ft_strcmp(cur->next->key, name) == 0)
    {
        hash* cur_next_next_copy = cur->next->next;
        free(cur->next->key);
        free(cur->next->data);
        free(cur->next);
        cur = cur_next_next_copy;
    }
}

/**
 * @brief Поиск элемента в хэш таблице
 * 
 * @param table Сама хэш таблица
 * @param phone_number Номер телефона 
 */
void find(hash ** table, char* phone_number)
{
    int hash_key = hash_func(phone_number);
	hash *cur = table[hash_key];

	if (cur == NULL)
    {
        printf("ERROR\n");
    }
	else if (ft_strcmp(cur->key, phone_number) == 0)
	{
		printf("%s %s\n", cur->key, cur->data);
	}
	else
	{
		while (cur->next != NULL && ft_strcmp(cur->next->key, phone_number) != 0)
		{
			cur = cur->next;
		}
		if (cur->next == NULL)
		{
			printf("ERROR\n");
		}
		else if (ft_strcmp(cur->next->key, phone_number) == 0)
		{
			printf("%s %s\n", cur->next->data, cur->next->key);
		}
		else
		{
			printf("ERROR\n");
		}
	}
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
    int strl = (int)strlen(key);
    for (int i = 0; i < strl; i++)
    {
        res = (res + key[strl - i - 1] * p) % mod;
        p *= mnoj;
    }
    res = res % mod;
    return (res > 0) ? res : mod + res;
}

void edit(hash ** table, char* phone_number, char* value)
{
    int hash_key = hash_func(phone_number);
	hash *cur = table[hash_key];

	if (cur == NULL)
    {
        printf("ERROR\n");
    }
	else if (ft_strcmp(cur->key, phone_number) == 0)
	{
		ft_strcpy(cur->data, value);
	}
	else
	{
		while (cur->next != NULL && ft_strcmp(cur->next->key, phone_number) != 0)
		{
			cur = cur->next;
		}
		if (cur->next == NULL)
		{
			printf("ERROR\n");
		}
		else if (ft_strcmp(cur->next->key, phone_number) == 0)
		{
			//printf("%s %s\n", cur->next->data, cur->next->key);
            ft_strcpy(cur->next->data, value);
		}
		else
		{
			printf("ERROR\n");
		}
	}
}

int main()
{
    freopen("tests.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int AMOUNT_OF_COMMANDS = 0;
    scanf("%d", &AMOUNT_OF_COMMANDS);
    hash** table = calloc(mod, sizeof(hash*));

    char* command = malloc(sizeof(char) * MAX_COMMAND_LEN);
    char* arg1 = malloc(sizeof(char) * MAX_STR_LEN);
    char* arg2 = malloc(sizeof(char) * MAX_STR_LEN);

    for (int i = 0; i < AMOUNT_OF_COMMANDS; i++)
    {
        scanf("%s", command);
        char sw = command[0];
        switch (sw)
        {
            case 'A':
            {
                scanf("%s %s", arg1, arg2);
                add(table, arg1, arg2);
                break;
            }
            case 'D':
            {
                scanf("%s", arg1);
                delete(table, arg1);
                break;
            }
            case 'P':
            {
                scanf("%s", arg1);
                find(table, arg1);
                break;
            }
            case 'E':
            {
                scanf("%s %s", arg1, arg2);
                edit(table, arg1, arg2);
                break;
            }
        }   
    }
}