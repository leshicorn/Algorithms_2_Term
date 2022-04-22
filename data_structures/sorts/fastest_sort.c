#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int get_chunk(unsigned Num, unsigned chunk, unsigned chunk_size, unsigned *mask_arr)
{
    return (mask_arr[chunk] & Num) >> (chunk * chunk_size);
}

void generate_masks(unsigned *mask_arr, unsigned chunks, unsigned chunk_size)
{
    for (unsigned int i = 0; i < chunks; i++)
    {
        unsigned mask = 0;
        for (unsigned int j = 0; j < chunk_size; j++)
        {
            mask |= 1 << (i * chunk_size + j);
        }
        mask_arr[i] = mask;
    }
}

void radix_sort(unsigned *begin, unsigned *val, unsigned int size, unsigned chunk, unsigned chunk_size, unsigned *mask_arr)
{
    unsigned power = 1 << chunk_size;
    unsigned *count = calloc(power, sizeof(unsigned));
    for (unsigned int i = 0; i < size; i++) {
        count[get_chunk(begin[i], chunk, chunk_size, mask_arr) + 1]++;
    }

    for (unsigned int i = 1; i < power; i++) {
        count[i] += count[i - 1];
    }

    for (unsigned int i = 0; i < size; i++) {
        val[count[get_chunk(begin[i], chunk, chunk_size, mask_arr)]++] =
            begin[i];
    }

    memcpy(begin, val, size * sizeof(unsigned));

    free(count);
}

void fast_sort(unsigned *begin, unsigned *end)
{
    unsigned chunk_size = 16,
            chunks = sizeof(unsigned) * 8 / chunk_size;
    unsigned *mask_arr = calloc(chunks, sizeof(unsigned));
    generate_masks(mask_arr, chunks, chunk_size);
    unsigned int size = end - begin;
    unsigned *val = calloc(size, sizeof(unsigned));

    for (unsigned int chunk = 0; chunk < chunks; chunk++) {
        radix_sort(begin, val, size, chunk, chunk_size, mask_arr);
    }

    free(val);
    free(mask_arr);
}

int main()
{
    unsigned array[8] = {9, 6, 5, 4, 3, 2, 1, 1};
    fast_sort(array, array + 8);

    for (unsigned int i = 0; i < 8; i++) {
        printf("%d ", array[i]);
    }
}