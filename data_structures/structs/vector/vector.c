#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define error_code -1
#define success 0

struct vector
{
	size_t elem_size;
	size_t size;
	size_t capasity;
	void* data;
};

struct vector* vector_new(size_t elems, size_t elem_size)
{
	struct vector* new_vector = malloc(sizeof(struct vector));

	if (!new_vector)
		return NULL;
	
	new_vector->elem_size = elem_size;
	new_vector->capasity = (elems << 1);
	new_vector->data = malloc(new_vector->capasity * new_vector->elem_size);
	new_vector->size = elems;

	if (!new_vector->data)
	{
		free(new_vector);
		new_vector = NULL;
		return NULL;
	}
	return new_vector;
}

int vector_push(struct vector* v, void const* elem)
{
	if (!v || !elem)
		return error_code;

	if (v->capasity == 0)
	{
		v->capasity = 10;
		void* new_data = realloc(v->data, v->capasity * v->elem_size);

		if (!new_data)
			return error_code;
		v->data = new_data;
	}

	if (v->size == v->capasity)
	{
		v->capasity <<= 1;
		void* new_data = realloc(v->data, v->capasity * v->elem_size);

		if (!new_data)
			return error_code;

		v->data = new_data;
	}

	void* cur_ptr = (char*)v->data + v->elem_size * v->size;
	memcpy(cur_ptr, elem, v->elem_size);
	++v->size;

	return success;
}

int vector_pop(struct vector* v, void* elem)
{
	if (!v || !v->size || !elem)
		return error_code;

	--v->size;

	void* cur_ptr = (char*)v->data + v->elem_size * v->size;
	memcpy(elem, cur_ptr, v->elem_size);

	return success;
}

struct vector* vector_delete(struct vector* v)
{
	if (v)
	{
		if (v->data)
		{
			free(v->data);
			v->data = NULL;
		}
		free(v);
		v = NULL;
	}
	return NULL;
}

int vector_set(struct vector* v, size_t index, void const *elem)
{
	if (!v || !elem || index >= v->size)
		return error_code;

	void* cur_ptr = (char*)v->data + v->elem_size * index;
	memcpy(cur_ptr, elem, v->elem_size);

	return success;
}

int vector_get(struct vector const* v, size_t index, void *elem)
{
	if (!v || !elem || index >= v->size)
		return error_code;

	void* cur_ptr = (char*)v->data + v->elem_size * index;
	memcpy(elem, cur_ptr, v->elem_size);

	return success;
}

int vector_reserve(struct vector* v, size_t new_capasity)
{
	if (!v)
		return error_code;

	if (new_capasity <= v->capasity)
		return success;

	v->capasity = new_capasity;
	void* new_data = realloc(v->data, v->capasity * v->elem_size);

	if (!new_data)
	{
		return error_code;
	}

	v->data = new_data;
	return success;
}

int vector_resize(struct vector *v, size_t new_size)
{
	if (!v)
	{
		return error_code;
	}

	if (v->capasity == 0)
	{
		int ok = vector_reserve(v, 10);
		if (ok == 1)
		{
			return error_code;
		}
	}

	if (new_size >= v->capasity)
	{
		int ok = vector_reserve(v, new_size * 2);
		if (ok)
			return error_code;
	}
	v->size = new_size;

	return success;
}

size_t vector_size(struct vector const* v)
{
	if (!v)
		return success;
	return v->size;
}

int vector_empty(struct vector const* st)
{
	size_t size = vector_size(st);
	return (size > 0 ? 0 : 1);
}

void vector_print(struct vector const* v, void (*pf)(void const* data))
{
	printf("[");
	void* current_pointer = NULL;

	for(int i = 0; i < v->size; i++)
	{
		current_pointer = (char*)v->data + i * v->elem_size;

		pf(current_pointer);
		if (i + 1 != v->size)
		{
			printf(", ");
		}
	}
	printf("]\n");
}