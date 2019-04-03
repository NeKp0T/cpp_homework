#include "clist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct position_node {
  int x, y;
  struct intrusive_node node;
} position_node;

void remove_position_node(intrusive_list *l, position_node* p) {
  remove_node(l, &p->node);
  free(p);
}

void remove_position(intrusive_list *l, int x, int y) { // removes all (x, y) pairs
  for (intrusive_node *i = l->head; i;) {
    intrusive_node *next = i->next;
    position_node *p = container_of(i, position_node, node);
    if (p->x == x && p->y == y)
      remove_position_node(l, p);

    i = next;
  }
}

void add_position(intrusive_list *l, int x, int y) {
  position_node* p = malloc(sizeof(position_node));
  p->x = x;
  p->y = y;
  add_node(l, &p->node);
}

void show_all_positions(intrusive_list *l) {
  for (intrusive_node *i = l->head; i; i = i->next) {
    position_node *p = container_of(i, position_node, node);
    printf("(%d %d) ", p->x, p->y);
  }
  printf("\n");
}

void remove_all_positions(intrusive_list *l) {
  for (intrusive_node *i = l->head; i;) {
    intrusive_node *next = i->next;
    position_node *p = container_of(i, position_node, node);
    remove_position_node(l, p);

    i = next;
  }
}

int main() {
  intrusive_list l;
  init_list(&l);

  char s[20];
  while (scanf("%s", s) > 0) {
    if (strcmp(s, "add") == 0) {
      int x, y;
      if (scanf("%d %d", &x, &y) != 2) {
        printf("Unknown command");
        continue;
      }
      add_position(&l, x, y);
    }
    else if (strcmp(s, "rm") == 0) {
      int x, y;
      if (scanf("%d %d", &x, &y) != 2) {
        printf("Unknown command");
        continue;
      }
      remove_position(&l, x, y);
    }
    else if (strcmp(s, "print") == 0) {
      show_all_positions(&l);
    }
    else if (strcmp(s, "rma") == 0) {
      remove_all_positions(&l);
    }
    else if (strcmp(s, "len") == 0) {
      printf("%d\n", get_length(&l));
    }
    else if (strcmp(s, "exit") == 0) {
      break;
    }
    else {
      printf("Unknown command\n");
    }
  }

  remove_all_positions(&l);

  return 0;
}
