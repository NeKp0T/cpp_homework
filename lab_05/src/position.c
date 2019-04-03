#include "position.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>

void remove_position_node(intrusive_list *l, position_node *p)
{
    remove_node(l, &p->node);
    free(p);
}

void remove_position(intrusive_list *l, int x, int y)
{ // removes all (x, y) pairs
    for (intrusive_node *i = l->head; i;)
    {
        intrusive_node *next = i->next;
        position_node *p = container_of(i, position_node, node);
        if (p->x == x && p->y == y)
            remove_position_node(l, p);

        i = next;
    }
}

void add_position(intrusive_list *l, int x, int y)
{
    position_node *p = malloc(sizeof(position_node));
    p->x = x;
    p->y = y;
    add_node(l, &p->node);
}

void show_all_positions(intrusive_list *l)
{
    for (intrusive_node *i = l->head; i; i = i->next)
    {
        position_node *p = container_of(i, position_node, node);
        printf("(%d %d) ", p->x, p->y);
    }
    printf("\n");
}

void remove_all_positions(intrusive_list *l)
{
    for (intrusive_node *i = l->head; i;)
    {
        intrusive_node *next = i->next;
        position_node *p = container_of(i, position_node, node);
        remove_position_node(l, p);

        i = next;
    }
}

void fwriteint3(unsigned int v, FILE* f) {
    fwrite(&v, 3, 1, f);
}

size_t freadint3(int *n, FILE* f) {
    *n = 0;
    size_t ret = fread(n, 3, 1, f);
    // if n < 0
    if (*n & (1 << 23))
        *n |= (-(1 << 24));
    return ret;
}

void loadtext(intrusive_list *l, FILE *f) {
    int x, y;
    while (fscanf(f, "%d %d\n", &x, &y) == 2)
        add_position(l, x, y);
    reverse_list(l);
}

void loadbin(intrusive_list *l, FILE *f) {
    int x = 0, y = 0;
    while (freadint3(&x, f) == 1) {
        freadint3(&y, f);
        add_position(l, x, y);
        x = 0, y = 0;
    }
    reverse_list(l);
}

void apply_fprint(intrusive_list *l, FILE* f, char* fmt) {
    char *q[2];
    q[0] = (char *)f;
    q[1] = fmt;
    apply(l, fprint, q);
}

// apply actions

void fprint(intrusive_node *p, void *mem) {
    FILE *fout = ((void **)mem)[0];
    char *s = ((void **)mem)[1];
    position_node *pos_node = container_of(p, position_node, node);
    fprintf(fout, s, pos_node->x, pos_node->y);
}

void fprintbin(intrusive_node *p, void *mem) {
    FILE *fout = mem;
    position_node *pos_node = container_of(p, position_node, node);
    fwriteint3(pos_node->x, fout);
    fwriteint3(pos_node->y, fout);
}

void count(intrusive_node *p, void *mem) {
  assert(p); // Warning unused parameter
  (*(int *)mem)++;
}

