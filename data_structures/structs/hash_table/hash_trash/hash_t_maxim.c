#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 100000
#define MAX_AMOUNT_OF_TABLES 10
#define MAX_STR_LEN 21

int hash_function(char* key)
{
	int sum = 0;
	int len = strlen(key);
	for (int i = 0; i < len; ++i)
		sum += key[i];
	return sum % CAPACITY;
}

struct hash_item {
	char* key;
	char* value;
};

typedef struct hash_item hash_item;

struct hash_table {
	int capacity;
	int size;
	hash_item** items;
};

typedef struct hash_table hash_table;

hash_item* create_hash_item(char* key, char* value) {
	hash_item* item = malloc(sizeof(hash_item));
	item->key = malloc(strlen(key) + 1);
	item->value = malloc(strlen(value) + 1);
	strcpy(item->key, key);
	strcpy(item->value, value);
	return item;
}

hash_table** create_table_array()
{
    hash_table** new = calloc(MAX_AMOUNT_OF_TABLES, sizeof(hash_table*));

    return new;
}

hash_table* create_hash_table()
{
	hash_table* new = malloc(sizeof(hash_table));
	new->capacity = CAPACITY;
	new->size = 0;
	new->items = calloc(CAPACITY, sizeof(hash_item*));
	return new;
}

void insert(hash_table* table, char* key, char* value) {
    if (table == NULL)
    {
        return;
    }
    
	int index = hash_function(key);
	// while (table->items[index] != NULL)
		// index++;

	//if (table->items[index] == NULL)
		table->items[index] = create_hash_item(key, value);
	//else
		//???
}

void erase(hash_table* hash_table, char* key)
{
    if (hash_table == NULL || key == NULL)
    {
        return;
    }
    int index = hash_function(key);
    if (strcmp(hash_table->items[index]->key, key) == 0)
    {
        // free(hash_table->items[index]->key);
        // free(hash_table->items[index]->value);
        hash_table->items[index]->key = NULL;
        hash_table->items[index]->value = NULL; 
    }
}

char* search(hash_table* hash_table, char* key) {
    if (hash_table == NULL || key == NULL)
    {
        return NULL;
    }
    
	int index = hash_function(key);
	while (hash_table->items[index] != NULL && strcmp(hash_table->items[index]->key, key) != 0)
		index++;
	if (hash_table->items[index] == NULL)
		return NULL;
	return hash_table->items[index]->value;
}

hash_table* mem_free(hash_table* table)
{
    table = NULL;
    return table;
}

int main()
{
    freopen("input.txt", "r", stdin);

    hash_table** array = create_table_array();

    char* command = calloc(MAX_STR_LEN, sizeof(char));
    char* value = calloc(MAX_STR_LEN, sizeof(char));
    char* key = calloc(MAX_STR_LEN, sizeof(char));
    char* to_print = calloc(MAX_STR_LEN, sizeof(char));
    int cur_table_number = -1;

    while (scanf("%s", command) != EOF)
    {
        if (command[0] == 'c')
        {
            scanf("%d", &cur_table_number);
            array[cur_table_number] = create_hash_table();
        }
        if (command[0] == 'i')
        {
            scanf("%d %s %s", &cur_table_number, key, value);
            insert(array[cur_table_number], key, value);
        }
        if (command[0] == 'e')
        {
            scanf("%d %s", &cur_table_number, key);
            erase(array[cur_table_number], key);
        }
        if (command[0] == 'f')
        {
            scanf("%d %s", &cur_table_number, key);
            to_print = search(array[cur_table_number], key);
            if (to_print == NULL)
            {
                printf("MISSING\n");
            }
            else
            {
                printf("%s\n", to_print);
            }
        }
        if (command[0] == 'd')
        {
            scanf("%d", &cur_table_number);
            array[cur_table_number] = mem_free(array[cur_table_number]);

        }
    }
}

/*int main() 
{
	hash_table* table = create_hash_table();
	insert(table, "ab", "123");
	insert(table, "ba", "124");
	insert(table, "3", "125");
	printf("%s\n", search(table, "ba"));
	printf("%s\n", search(table, "ab"));
	if (search(table, "4"))
		printf("%s\n", search(table, "4"));
	else
		printf("NOT FOUND\n");
	return 0;
}*/