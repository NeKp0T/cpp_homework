#include "clist.h"
#include <stdlib.h>
#include <stddef.h>


void init_list(struct intrusive_list *l) {
    l->head = NULL;
}

void add_node(intrusive_list *l, intrusive_node *node) {
    if (l->head)
        l->head->prev = node;
    node->next = l->head;
    node->prev = NULL;
    l->head = node;
}

void remove_node(intrusive_list *l, intrusive_node *node) {
    if (node == l->head)
        l->head = node->next;
    else
        node->prev->next = node->next;

    if (node->next)
        node->next->prev = node->prev;
}

int get_length(intrusive_list *l) {
    int q = 0;
    for (intrusive_node *i = l->head; i; i = i->next)
        q++;
    return q;
}

void reverse_node(intrusive_node *n) {
    intrusive_node *tmp = n->prev;
    n->prev = n->next;
    n->next = tmp;
}

void reverse_list(intrusive_list *l) {
    if (l->head == NULL)
        return;
    intrusive_node *i = l->head;
    for (; i && i->next != NULL; i = i->prev)
        reverse_node(i);
    l->head = i;
    reverse_node(i);
}

void apply(intrusive_list *l, void (*op)(intrusive_node *p, void *op_mem), void *op_mem) {
    for (intrusive_node *i = l->head; i; i = i->next)
        op(i, op_mem);
}