#include "mergesort.h"
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void cpymem(void *dest, const void *src, size_t n) {
    char *d = dest;
    const char *s = src;
    for (size_t i = 0; i < n; i++)
        *(d++) = *(s++);
}
void merge_buff(void *lb, void *rb, size_t lnum, size_t rnum, size_t size, int (*compar)(const void *, const void *), void* buff) {
    size_t li = 0;
    size_t ri = 0;
    char *l = lb;
    char *r = rb;
   char *out = buff;
    while (li < lnum && ri < rnum)
    {
        if (compar(l, r) < 0) {
            cpymem(out, l, size);
            l += size;
            li++;
        } else {
            cpymem(out, r, size);
            r += size;
            ri++;
        }
        out += size;
    }

    cpymem(out, l, (lnum - li) * size);
    out += lnum - li;
    cpymem(out, r, (rnum - ri) * size);
    out += rnum - ri;

    cpymem(lb, buff, size * (lnum + rnum));
}

// return int!!
int mergesort(void *base, size_t num, size_t size, int (*compar)(const void *, const void *)) {
    void *buff = malloc(size * num);
    mergesort_rec(base, num, size, compar, buff);
    free(buff);
    return 0;
}

void mergesort_rec(void *base, size_t num, size_t size, int (*compar)(const void *, const void *), void* buff) {
    if (num == 1)
        return;
    
    size_t mid = num / 2;
    void *rbase = (char *)base + size * mid;

    mergesort_rec(base, mid, size, compar, buff);
    mergesort_rec(rbase, num - mid, size, compar, buff);
    merge_buff(base, rbase, mid, num - mid, size, compar, buff);
}