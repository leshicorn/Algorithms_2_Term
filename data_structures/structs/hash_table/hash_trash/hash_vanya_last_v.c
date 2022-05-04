#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define mod 999983
#define mnoj 20029

typedef struct node
{
	char* key;
	char* val;
} Node;

typedef struct hash_table
{
	struct list** arr;
	size_t size;
} Hashtable;

typedef struct list
{
	Node elem;
	struct list* next;
} List;

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

List* list_new(char* key, char* val)
{
	List* head = (List*)calloc(1, sizeof(List));
	head->next = NULL;
    
	head->elem.key = calloc(21, sizeof(char));
	head->elem.val = calloc(21, sizeof(char));
    strcpy(head->elem.key, key);
    strcpy(head->elem.val, val);
	return head;
}

List *list_insert(List* head, char* key, char* val)
{
	if (head == NULL)
	{
		head = list_new(key, val);
		return head;
	}
	else
	{
		List* current = head;
		while (current->next != NULL)
			current = current->next;
		current->next = list_new(key, val);
		return head;
	}
}

List* list_find_before(List* head, char* key)
{
	if (head == NULL || strcmp(head->elem.key, key) == 0)
		return NULL;
	else
	{
		List* current = head;
		while (current->next != NULL && strcmp(current->next->elem.key, key) != 0)
			current = current->next;
		if (current->next == NULL)
			return NULL;
		else
			return current;
	}
}

List* list_find(List* head, char* key)
{
	if (head == NULL || strcmp(head->elem.key, key) == 0)
		return head;
	else
	{
		List* find = list_find_before(head, key);
		if (find == NULL)
			return NULL;
		else
			return find->next;
	}
}

List* list_delete(List* head)
{
	if (head == NULL)
		return NULL;
	else
	{
		list_delete(head->next);
		free(head);
		head = NULL;
		return head;
	}
}

List* list_erase(List* head, char* key)
{
	if (head == NULL)
		return NULL;
	if (strcmp(head->elem.key, key) == 0)
	{
		List* delete = head;
		head = head->next;
		free(delete->elem.key);
		free(delete->elem.val);
		free(delete);
		return head;
	}
	else
	{
		List* prev_found = list_find_before(head, key);
		if (prev_found == NULL)
			return head;
		else
		{
			List* delete = prev_found->next;
			prev_found->next = prev_found->next->next;
			free(delete->elem.key);
			free(delete->elem.val);
			free(delete);
			delete = NULL;
			return head;
		}
	}
}

Hashtable* hashtable_create(size_t size)
{
	Hashtable* new = calloc(1, sizeof(Hashtable));
	new->arr = calloc(size, sizeof(List*));
	new->size = size;
	return new;
}

Hashtable* hashtable_insert(Hashtable* table, char* key, char* val)
{
	int hash = hash_func(key);
	List *find = list_find(table->arr[hash], key);
	if (find == NULL)
		table->arr[hash] = list_insert(table->arr[hash], key, val);
	else
		strcpy(find->elem.val, val);
	return table;
}

Hashtable* hashtable_delete(Hashtable* removed)
{
	if (removed == NULL)
		return NULL;
	for (int i = 0; i < removed->size; i++)
		list_delete(removed->arr[i]);
	free(removed->arr);
	free(removed);
	return NULL;
}

int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    
	Hashtable** table = calloc(10, sizeof(Hashtable*));

	char* key = calloc(21, sizeof(char));
	char* val = calloc(21, sizeof(char));
	char* sw = calloc(11, sizeof(char));
	int n = 0;
	while(scanf("%10s", sw) > 0)
	{
		switch(sw[0])
		{
			case 'c':
			{
				scanf("%d", &n);
				table[n] = hashtable_create(mod);
				break;
			}
			case 'i':
			{
				scanf("%d %20s %20s", &n, key, val);
				if (table[n] == NULL)
					break;
				table[n] = hashtable_insert(table[n], key, val);
				break;
			}
			case 'f':
			{
				if (table[n] == NULL)
				{
					printf("MISSING\n");
					break;
				}
				scanf("%d %20s", &n, key);
				int hash = hash_func(key);
				List* found = list_find(table[n]->arr[hash], key);
				if (found == NULL)
				{
					printf("MISSING\n");
					free(found->elem.key);
					free(found->elem.val);
					free(found);
					break;
				}
				else
				{
					printf("%s\n", found->elem.val);
					break;
				}
			}
			case 'e':
			{
				scanf("%d %20s", &n, key);
				int hash = hash_func(key);
				table[n]->arr[hash] = list_erase(table[n]->arr[hash], key);
			}
			case 'd':
			{
				scanf("%d", &n);
				table[n] = hashtable_delete(table[n]);
				break;
			}
		}
	}
	free(table);
	free(key);
	free(val);
	free(sw);
    return 0;
}