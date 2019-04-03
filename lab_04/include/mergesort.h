#include <stdlib.h>
#include <stddef.h>

int mergesort(void *base, size_t num, size_t size, int (*compar)(const void *, const void *));

void mergesort_rec(void *base, size_t num, size_t size, int (*compar)(const void *, const void *), void *buff);

void merge_buff(void *lb, void *rb, size_t lnum, size_t rnum, size_t size, int (*compar)(const void *, const void *), void *buff);

void cpymem(void *dest, const void *src, size_t n);