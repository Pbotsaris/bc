#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdio.h>
#include "./tokenizer.h"

typedef struct node{
  long int      value;
  int           height;
  type_t        type;
  struct node   *left;
  struct node   *right;
}node_t;

typedef struct tree{
  node_t       *root;
  /* METHOD */
  void         (*free_all) (struct tree*);
  void         (*print) (struct tree*);
}tree_t;

void init_tree(tree_t *tree);

#endif
