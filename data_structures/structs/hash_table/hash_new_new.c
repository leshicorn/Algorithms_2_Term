#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mod 1033
#define mnoj 53
#define MAX_STR_LEN 31
#define MAX_AMOUNT_OF_TABLES 10

int array[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

typedef struct node
{
    char* key;
    char* value;
    struct node* next;
} node;

typedef struct table_arr
{
    node** table;
} table_arr;

int ft_strcmp(char* s1, char* s2)
{
    while (*s1 == *s2 && *s1 && *s2)
    {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

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

node** create_table()
{
    node** table = malloc(sizeof(struct node*) * mod);
    if (table == NULL)
    {
        printf("couldn't allocate memory allocate for 'table'\n");
        return NULL;
    }

    return table;
}

void insert(node** table, char* key, char* value)
{
    if (table == NULL)
    {
        printf("hui\n");
        return;
    }

    int hash = hash_func(key);
    table[hash] = malloc(sizeof(struct node*) * 100);
    node* cur = table[hash];

    if (table[hash]== NULL)
    {
        table[hash] = malloc(sizeof(node));
        table[hash]->key = malloc(sizeof(char) * MAX_STR_LEN);
        table[hash]->value = malloc(sizeof(char) * MAX_STR_LEN);
        table[hash]->key = strcpy(table[hash]->key, key);
        table[hash]->value = strcpy(table[hash]->value, value);
        table[hash]->next = NULL;
    }
    else // Для уже существующего ключа значение должно поменяться на новое. 
    {
        /*while (cur->next != NULL)
		{
			cur = cur->next; //Случай, когда не меняем значение, а 'дописываем дальше'
		}*/
        cur->key = malloc(sizeof(char) * MAX_STR_LEN);
        cur->value = malloc(sizeof(char) * MAX_STR_LEN);
        cur->key = strcpy(cur->key, key);
        cur->value = strcpy(cur->value, value);
        cur->next = NULL;
    }
}

void erase(node** table, char* key)
{
    if (table == NULL)
        return;
    int hash = hash_func(key);
    table[hash] = malloc(sizeof(node*) * 100);
    node* cur = table[hash];
    
    if (cur == NULL || cur->key == NULL || cur->value == NULL)
    {
        // printf("MISSING\n");
        return;
    }
    else
    {
        if (ft_strcmp(cur->key, key) == 0)
        {
            free(cur->key);
            free(cur->value);
            free(cur->next);
            cur->next = NULL;
            free(cur);
        }
    }
}

void find(node** table, char* key)
{
    if (table == NULL)
    {
        printf("MISSING\n");
        return;
    }
    int hash = hash_func(key);
    node* cur = table[hash];
    if (cur == NULL || cur->key == NULL || cur->value == NULL)
    {
        printf("MISSING\n");
        return;
    }
    else if (ft_strcmp(cur->key, key) == 0)
	{
		printf("%s\n", cur->value);
        return;
	}
    else
    {
        printf("MISSING\n");
        return;
    }
}

void destroy(node** table)
{
    if (table == NULL)
        return;
    for (int i = 0; i < mod; i++)
    {
        free(table[i]);
        table[i] = NULL;
    }
    free(table);
    table = NULL;
}

int main()
{
    freopen("input.txt", "r", stdin);
    // node** table = create_table();
    table_arr* arr = calloc(MAX_AMOUNT_OF_TABLES, sizeof(table_arr));
    int number = 0;

    int n = 1;
    
    while (n > 0 && n < 3)
    {
        char* command = calloc(MAX_STR_LEN, sizeof(char));
        char* value = calloc(MAX_STR_LEN, sizeof(char));
        char* key = calloc(MAX_STR_LEN, sizeof(char));

        n = scanf("%s", command);
        if (command[0] == 'c')
        {
            n += scanf("%d", &number);
            arr[number].table = create_table();
            array[number] = 1;
        }
        else if (command[0] == 'i')
        {
            scanf("%d %s %s", &number, key, value);
            insert(arr[number].table, key, value);
        }
        else if (command[0] == 'e')
        {
            scanf("%d %s", &number, key);
            erase(arr[number].table, key);
        }
        else if (command[0] == 'f')
        {
            scanf("%d %s", &number, key);
            if (array[number] == 0)
                printf("MISSING\n");
            else
                find(arr[number].table, key);
        }
        else if (command[0] == 'd')
        {
            scanf("%d", &number);
            array[number] = 0;
            destroy(arr[number].table);
        }
        free(command);
        free(key);
        free(value);
    }

    for (int i = 0; i < 10; i++)
    {
        if (array[i] == 1)
        {
            array[i] = 0;
            destroy(arr[i].table);
        }
    }
    return 0;
}