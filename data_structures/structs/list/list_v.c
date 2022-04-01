#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct list 
{
    int elem;
    struct list *next;
    struct list *prev;
};

struct list *list_new(int elem)
{
    struct list *head = (struct list *)malloc(sizeof(struct list));
    head->elem = elem;
    head->next = NULL;
    head->prev = NULL;

    return head;
}


struct list* getlast(struct list *head) 
{
    if (head == NULL) 
    {
        return NULL;
    }
    while (head->next) 
    {
        head = head->next;
    }

    return head;
}

int list_is_empty(const struct list *head)
{
    return (head == NULL);
}

struct list *list_insert(struct list *head, int elem)
{
    
    if (head == NULL)
    {
        head = (struct list *)malloc(sizeof(struct list));
        head->elem = elem;
        head->next = NULL;
        head->prev = NULL;
        return head;
    }
    else
    {
        struct list *last = getlast(head);
        struct list *tmp = (struct list*) malloc(sizeof(struct list));
        tmp->elem = elem;
        tmp->next = NULL;
        tmp->prev = last;
        last->next = tmp;
        return head;
    }
}

struct list *list_find(struct list *head, int elem)
{
    while (head->elem != elem && head->next != NULL)
    {
        head = head->next;
    }
    if (head->elem == elem)
    {
        return head;
    }
    else
    {
        return NULL;
    }
}

struct list *list_find_prev(struct list *head, struct list *what)
{
    int elem = what->elem;
    while (head->elem != elem && head->next != NULL)
    {
        head = head->next;
    }
    if (head->elem == elem)
    {
        return head->prev;
    }
    else
    {
        return NULL;
    }
}

struct list *list_erase(struct list *head, int elem)
{
    struct list *tmp = head;
    while (tmp->next->elem != elem && tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    if (tmp->next == NULL)
    {
        return head;
    }
    else
    {
        tmp->next = tmp->next->next;
        return head;
    }
}

struct list *list_insert_after(struct list *head, struct list *where, struct list *what)
{
    if (list_is_empty(head))
    {
        return list_new(what->elem);
    }

    if (what == NULL || where->next == NULL)
    {
        return head;
    }
    else
    {
        what->next = where->next;
        where->next = what;
        what->prev = where;
        return head;
    }
}

struct list *list_insert_before(struct list *head, struct list *where, struct list *what)
{
    if (list_is_empty(head))
    {
        return list_new(what->elem);
    }

    if (what == NULL || where->next == NULL)
    {
        return head;
    }
    else
    {
        head = list_insert_after(head, list_find_prev(head, where), what);
        return head;
    }
}

struct list *list_delete(struct list *head) 
{
    struct list *current = head;
    struct list *next = NULL;
    
    while (current != NULL) 
    {
        next = current->next;
        free(current);
        current = next;
    }
    return NULL;
}

void list_printer(const struct list *head) 
{
    struct list *l_copy = (struct list*)head;
    if (list_is_empty(l_copy))
        return;
    
    printf("[");
    while (head->next->next != NULL) 
    {
        printf("%d, ", head->elem);
        head = head->next;
    }

    printf("%d, ", head->elem);
    head = head->next;

    printf("%d", head->elem);
    printf("]\n");
}

void list_print(struct list const *head) 
{
    struct list *current = (struct list*) *(&head);
    struct list *next = NULL;

    printf("[");
    while (current != NULL) 
    {
        next = current->next;
        if (next == NULL) 
            printf("%d", current->elem);
        else 
            printf("%d, ", current->elem);
        current = next;
    }
    printf("]\n");
}

struct list *list_next(struct list *curr)
{
    if (curr->next == NULL)
    {
        return NULL;
    }
    else
    {
        return curr->next;
    }
}

/*int main()
{
    struct list *head = NULL;
    head = list_insert(head, 1);
    list_insert(head, 2);
    list_insert(head, 3);
    list_insert(head, 4);
    list_insert(head, 5);
    list_print(head);
    struct list a;
    a.elem = 666;
    a.next = list_find(head, 3);
    struct list d;
    d.elem = 333;
    struct list *b = list_find(head, 2);
    struct list *c = list_find_prev(head, b);
    printf("*%d*\n", c->elem);
    list_insert_after(head, b, &d);
    list_print(head);
    list_insert_before(head, b, &a);
    list_print(head);
    return 0;
}*/

/*int main() 
{
    struct list *head = NULL;
    list_print(head);
    
   struct list* b = list_find(head, 2);
    printf("%d\n", b->elem);

    list_erase(head, 7);
    list_print(head);
    struct list a;
    a.elem = 323;
    head = list_insert_before(head, head, &a);
    
    list_print(head);

    struct list h;
    h.elem = 345;
    list_insert_before(head, b, &h);
    list_print(head);

    struct list* c = list_find(head, 14);
    struct list* d = list_next(c);
    if (d == NULL)
    {
        printf("Oshibka");
        return 0;
    }
    printf("Found next: %d\n", d->elem);


    
}*/

int main() {
    struct list *head = list_new(0);
    head = list_insert(head, 1);
    list_print(head);
    head = list_delete(head);
    list_print(head);
}

/*int main()
{
    struct list *head = NULL;
    head = list_insert(head, 1);
    list_insert(head, 2);
    list_insert(head, 3);
    list_insert(head, 4);
    list_insert(head, 5);
    list_print(head);
    struct list a;
    a.elem = 666;
    a.next = list_find(head, 3);
    struct list d;
    d.elem = 333;
    struct list *b = list_find(head, 2);
    struct list *c = list_find_prev(head, b);
    printf("*%d*\n", c->elem);
    list_insert_after(head, b, &d);
    list_print(head);
    list_insert_before(head, b, &a);
    list_print(head);
    return 0;
}*/