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
