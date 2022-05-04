#include <stdio.h>
#include <stdlib.h>

#define mod 505601
#define mnoj 8147

//#define mod 1033
//#define mnoj 53

typedef struct List
{
    int value;
    int key;
    struct List *next;
} list;

list *list_find(list *head, int key)
{
    list *current = head;

    if (head == NULL)
        return NULL;

    if (head -> key == key) 
        return head;
    
    while (current != NULL)
    {
        if (current -> key == key) 
            return current;
        current = current -> next;
    }
    return NULL;
}

int len(int a)
{
    int count = 0;
    while(a > 0)
    {
        a /= 10;
        count++;
    }
    return count;
}

int keymaker(int name)
{
    int res = 0;
    int p = 1;  
    int l = len(name);
    for (int i = 0; i < l; i++)
    {   
        int n = name % 10;
        res = (res + n * p) % mod;
        p *= mnoj;
        name /= 10;
    }
    res = res % mod;
    return (res > 0) ? res : mod + res;
}

list *list_new(int key, int value) 
{
    list* new_list = (list*)malloc(sizeof(list));
    new_list -> next = NULL;
    new_list -> value = value;
    new_list -> key = key;
    return new_list;
}

list *list_insert(list *head, int key, int value)
{
    if(list_find(head, key) != NULL)
    {
        printf("ERROR\n");
        return head;
    }

    list *current = head;

    if (head == NULL) 
        return list_new(key, value);

    while (current -> next != NULL) 
    {
        current = current -> next;
    }
    current -> next = list_new(key, value);
    return head;
}

list *list_erase(list *head, int key)
{
    if(list_find(head, key) == NULL)
    {
        printf("ERROR\n");
        return head;
    }

    list *current = head;
    list *next = NULL;

    if (head == NULL)
        return head;

    if (head -> key == key)
    {
        list *delete = head;
        head = head -> next;
        free(delete);
        return head;
    }

    while (current != NULL)
    {
        next = current -> next;
        if (next == NULL) 
            break;
        if (next -> key == key)
        {
            list *delete = current -> next;
            current -> next = next -> next;
            free(delete);
            break;
        }
        current = next;
    }
    return head;
}

list *list_delete(list *head)
{
    list *current = head;
    list *next = NULL;
    
    while (current != NULL)
    {
        next = current -> next;
        free(current);
        current = next;
    }

    return NULL;
}

int swap(list** table, int val1, int val2)
{
	int res = 0;
	int hash1 = keymaker(val1), hash2 = keymaker(val2);
	list* item1 = list_find(table[hash1], val1);
	list* item2 = list_find(table[hash2], val2);

	if (item1 == NULL)
	{
		if (item2 == NULL)
		{
			res = abs(val1 - val2);
			table[hash1] = list_insert(table[hash1], val1, val2);
			table[hash2] = list_insert(table[hash2], val2, val1);
		}
		else
		{
			res = abs(val1 - item2->value);
			table[hash1] = list_insert(table[hash1], val1, item2->value);
			item2->value = val1;
		}
	}
	else
	{
		if (item2 == NULL)
		{
			res = abs(item1->value - val2);
			table[hash2] = list_insert(table[hash2], val2, item1->value);
			item1->value = val2;
		}
		else
		{
			res = abs(item1->value - item2->value);
			int temp = item1->value;
			item1->value = item2->value;
			item2->value = temp;
		}
	}
	return res;
}

int main()
{
   // freopen("input.txt", "r", stdin);
    list** table = calloc(mod, sizeof(list*));
    int n = 0, val1 = 0, val2 = 0;
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &val1, &val2);
		printf("%d\n", swap(table, val1, val2));
	}

    for (int i = 0; i < mod; i++)
    {
        table[i] = list_delete(table[i]);
    }
    free(table);
    return 0;
}