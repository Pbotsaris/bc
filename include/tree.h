#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdio.h>

typedef enum node_type{NUMERIC_LITERAL}node_type_t;

typedef struct node{
  node_type_t type;
  long int value;
  int height;
  struct node *left;
  struct node *right;
}node_t;

typedef struct tree{
  struct node *root;
  int count;
  int height;
  void (*add) (struct tree*, long int);
  void (*get_height) (struct tree*);
  void (*free_all) (struct tree*);
  void (*print) (struct tree*);
}tree_t;

void init_tree(tree_t *tree);

#endif
