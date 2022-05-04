#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define mod 1033
#define mnoj 53
#define MAX_STR_LEN 31

typedef struct list
{
    struct list *next;
    char* value;
    char* key;
}list;

typedef struct table
{
    char* name;
    int result;
    int attempt;
} table;

list *list_find(list *head, char* key)
{
    list *current = head;

    if (head == NULL || strcmp(head->key, key) == 0) 
        return head;
    
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0) 
            return current;
        current = current->next;
    }
    return NULL;
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

list *list_new(char* key, char* value) 
{
    list* new_list = (list*)malloc(sizeof(list));
    new_list->next = NULL;
    new_list->value = malloc(MAX_STR_LEN * sizeof(char));
    new_list->key = malloc(MAX_STR_LEN * sizeof(char));
    strcpy(new_list->value, value);
    strcpy(new_list->key, key);
    return new_list;
}

list *list_insert(list *head, char* key, char* value)
{
    if(list_find(head, key) != NULL)
    {
        printf("ERROR\n");
        return head;
    }

    list *current = head;

    if (head == NULL) 
        return list_new(key, value);

    while (current->next != NULL) 
    {
        current = current->next;
    }
    current->next = list_new(key, value);
    return head;
}

list *list_erase(list *head, char* key)
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

    if (strcmp(head->key, key) == 0)
    {
        list *delete = head;
        head = head->next;
        free(delete);
        return head;
    }

    while (current != NULL)
    {
        next = current->next;
        if (next == NULL) 
            break;
        if (strcmp(next->key, key) == 0)
        {
            list *delete = current->next;
            current->next = next->next;
            free(delete);
            break;
        }
        current = next;
    }
    return head;
}

list* edit_phone(list *head, char* key, char* value)
{
    if(list_find(head, key) == NULL)
    {
        printf("ERROR\n");
        return head;
    }
    list* found = list_find(head, key);
    strcpy(found->value, value);
    return head;
}

list *list_delete(list *head)
{
    list *current = head;
    list *next = NULL;
    
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    return NULL;
}

int main()
{
    int n;
    char sur[30], sw[10], tel[30];
    list *table[mod];

    for (int i = 0; i < mod; i++)
    {
        table[i] = NULL;
    }
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%10s", sw);
        if (strcmp(sw, "ADD") == 0)
        {
            scanf("%30s %30s", sur, tel);
            int hash = hash_func(sur);
            table[hash] = list_insert(table[hash], sur, tel);
        }
        if (strcmp(sw, "DELETE") == 0)
        {
            scanf("%30s", sur);
            int hash = hash_func(sur);
            table[hash] = list_erase(table[hash], sur);
        }
        if (strcmp(sw, "EDITPHONE") == 0)
        {
            scanf("%30s %30s", sur, tel);
            int hash = hash_func(sur);
            table[hash] = edit_phone(table[hash], sur, tel);
        }
        if (strcmp(sw, "PRINT") == 0)
        {
            scanf("%30s", sur);
            int hash = hash_func(sur);
            list* tmp = list_find(table[hash], sur);
            if (tmp == NULL)
            {
                printf("ERROR\n");
            }
            else
            {
                printf("%s %s\n", tmp->key, tmp->value);
            }
        }       
    }
}