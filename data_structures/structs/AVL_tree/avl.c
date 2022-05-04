#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node // структура для представления узлов дерева
{
	char* key;
	char* value;
	unsigned char height;
	struct node* left;
	struct node* right;
}tree;

enum TreeWalkType { PRE_ORDER, IN_ORDER, OUT_ORDER };

tree* find(tree* p, char* k);

int cmp(char* a, char* b)
{
    int len_a = strlen(a), len_b = strlen(b);
    int i = 0;
    while(i < len_a + len_b)
    {
        if(a[i] > b[i])
        {
            return 1;
        }
        if(a[i] < b[i])
        {
            return 0;
        }
        i++;
		if (i == len_a)
		{
			return 0;
		}
		if (i == len_b)
		{
			return 1;
		}
    }
    return 0;
}

unsigned char height(tree* p)
{
	return p?p->height:0;
}

int bfactor(tree* p)
{
	return height(p->right)-height(p->left);
}

void fixheight(tree* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

tree* rotateright(tree* p) // правый поворот вокруг p
{
	tree* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

tree* rotateleft(tree* q) // левый поворот вокруг q
{
	tree* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

tree* balance(tree* p) // балансировка узла p
{
	fixheight(p);
	if(bfactor(p) == 2)
	{
		if(bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if(bfactor(p) == -2)
	{
		if(bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}

tree* insert(tree* p, char* k, char* value) // вставка ключа k в дерево с корнем p
{
	if (find(p, k) != NULL)
	{
		tree* found = find(p, k);
		strcpy(found->value, value);
		return p;
	}
	
	if(p == NULL)
	{	
		// return new node(k);
		tree* new = malloc(1 * sizeof(tree));
		new->key = malloc(21 * sizeof(char));
		strcpy(new->key, k);
		new->value = malloc(21 * sizeof(char));
		strcpy(new->value, value);
		new->left = NULL;
		new->right = NULL;
		new->height = 1;
		return new;
	}	
	if(cmp(p->key, k))
		p->left = insert(p->left, k, value);
	else
		p->right = insert(p->right, k, value);
	return balance(p);
}

tree* findmin(tree* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left?findmin(p->left):p;
}

tree* removemin(tree* p) // удаление узла с минимальным ключом из дерева p
{
	if(p->left == NULL)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

tree* erase(tree* p, char* k) // удаление ключа k из дерева p
{
	if(p == NULL) return NULL;
	if(cmp(p->key, k))
		p->left = erase(p->left,k);
	else if(k > p->key)
		p->right = erase(p->right,k);	
	else //  k == p->key 
	{
		tree* q = p->left;
		tree* r = p->right;
		free(p);
		if(r == NULL) return q;
		tree* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

tree* find(tree* p, char* k)
{
	if (p == NULL)
	{
		return NULL;
	}
	if (strcmp(p->key, k) == 0)
	{
		return p;
	}
	if (cmp(p->key, k))
	{
		return find(p->left, k);
	}
	if (cmp(k, p->key))
	{
		return find (p->right, k);
	}
	return NULL;
}

void free_tree(tree* tree)
{
	if (tree->left != NULL)
	{
		free_tree(tree->left);
	}

}



void tree_vertex_walk(tree *top, void (*work)(tree *),
                      enum TreeWalkType type) {
    if (type == PRE_ORDER) work(top);
    if (top->left != NULL) tree_vertex_walk(top->left, work, type);
    if (type == IN_ORDER) work(top);
    if (top->right != NULL) tree_vertex_walk(top->right, work, type);
    if (type == OUT_ORDER) work(top);
}

void tree_vertex_destroy(tree *vertex) {
    if (!vertex) return;
    free(vertex->key);
    free(vertex->value);
    free(vertex);
}

tree *tree_destroy(tree *tree) {
    if (!tree) return NULL;
    tree_vertex_walk(tree, tree_vertex_destroy, OUT_ORDER);
    return NULL;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	char* c = malloc(10 * sizeof(char));
    char* key = malloc(21 * sizeof(char));
    char* value = malloc(21 * sizeof(char));
	tree* tree_new = NULL;
    while(scanf("%10s", c) > 0)
    {
        char sw = c[0];
        switch(sw)
        {
            case 'i':
            {
                scanf("%20s %20s", key, value);
                tree_new = insert(tree_new, key, value);
                break;
            }
            case 'e':
            {
                scanf("%20s", key);
                tree_new = erase(tree_new, key);
                break;
            }
            case 'f':
            {
                scanf("%20s", key);
                if (find(tree_new, key) == NULL)
                {
                    printf("MISSING\n");
                    break;
                }
                else
                {
					tree* found = find(tree_new, key);
                    printf("%s\n", found->value);
                    break;
                }
            }
        }
    }

	tree_destroy(tree_new);
	free(c);
	free(key);
	free(value);

	return 0;
}