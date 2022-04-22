#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mod 1033
#define mnoj 53
#define MAX_STR_LEN 31
#define MAX_AMOUNT_OF_TABLES 10

int arr[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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
        /*while (cur->next != NULL && ft_strcmp(cur->next->key, key) != 0)
            cur = cur->next;
        if (ft_strcmp(cur->next->key, key) == 0)
        {
            node* cur_next_next_copy = cur->next->next;
            free(cur->next->key);
            free(cur->next->value);
            free(cur->next);
            cur = cur_next_next_copy;
        }*/
        
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
        /*while (cur->next != NULL && ft_strcmp(cur->next->key, key) != 0)
            cur = cur->next;
        if (cur->next == NULL)
        {
            printf("MISSING\n");
            return;
        }
        else if (ft_strcmp(cur->key, key) == 0)
        {
            printf("%s\n", cur->next->value);
        }
        else if (ft_strcmp(cur->next->key, key) == 0)
		{
			printf("%s\n", cur->next->value);
		}
		else
		{
			printf("MISSING\n");
		}*/
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
    node** table = create_table();

    // char* command = malloc(sizeof(char) * MAX_STR_LEN);
    // char* value = malloc(sizeof(char) * MAX_STR_LEN);
    // char* key = malloc(sizeof(char) * MAX_STR_LEN);
    int number = 0;
    //int hash = 0;

    int n = 1;
    // while (n != 0)
    //for (int i = 0; i < 10; i++)
    while (n > 0 && n < 3)
    {
        char* command = calloc(MAX_STR_LEN, sizeof(char));
        char* value = calloc(MAX_STR_LEN, sizeof(char));
        char* key = calloc(MAX_STR_LEN, sizeof(char));

        //printf("%d\t", n);

        n = scanf("%s", command);
        if (command[0] == 'c')
        {
            n += scanf("%d", &number);
            table = create_table();
            arr[number] = 1;
        }
        else if (command[0] == 'i')
        {
            scanf("%d %s %s", &number, key, value);
            // hash = hash_func(key);
            insert(table, key, value);
        }
        else if (command[0] == 'e')
        {
            scanf("%d %s", &number, key);
            erase(table, key);
        }
        else if (command[0] == 'f')
        {
            scanf("%d %s", &number, key);
            if (arr[number] == 0)
                printf("MISSING\n");
            else
                find(table, key);
        }
        else if (command[0] == 'd')
        {
            scanf("%d", &number);
            arr[number] = 0;
            destroy(table);
        }
        free(command);
        free(key);
        free(value);
    }
}

/*int main()
{
    freopen("input.txt", "r", stdin);
    table_arr* arr = calloc(MAX_AMOUNT_OF_TABLES, sizeof(table_arr));
    char* command = malloc(sizeof(char) * MAX_STR_LEN);
    char* value = malloc(sizeof(char) * MAX_STR_LEN);
    char* key = malloc(sizeof(char) * MAX_STR_LEN);
    int number = 0;
    int hash = 0;

    int n = 1;
    while (n >= 1 && n <= 3)
    {
        scanf("%s", command);
        if (command[0] == 'c')
        {
            scanf("%d", &number);
            arr[number].table = create_table();
        }
        else if (command[0] == 'i')
        {
            scanf("%d %s %s", &number, key, value);
            hash = hash_func(key);
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
            find(arr[number].table, key);
        }
        else if (command[0] == 'd')
        {
            scanf("%d", &number);
            destroy(arr[number].table);
        }
    }
    printf("finished\n");
    free(command);
    free(value);
    free(key);
}*/