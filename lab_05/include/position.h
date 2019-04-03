#ifndef _POSITION_11102017_
#define _POSITION_11102017_

#include "clist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct position_node
{
    int x, y;
    struct intrusive_node node;
} position_node;

void remove_position_node(intrusive_list *l, position_node *p);

void remove_position(intrusive_list *l, int x, int y);

void add_position(intrusive_list *l, int x, int y);

void show_all_positions(intrusive_list *l);

void remove_all_positions(intrusive_list *l);

void loadtext(intrusive_list *l, FILE *f);
void loadbin(intrusive_list *l, FILE *f);

void apply_fprint(intrusive_list *l, FILE *f, char *fmt);

void print(intrusive_node *p, void *mem);
void fprint(intrusive_node *p, void *mem);
void fprintbin(intrusive_node *p, void *mem);

void count(intrusive_node *p, void *mem);

#endif