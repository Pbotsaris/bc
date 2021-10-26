/*
 * =====================================================================================
 *
 *       Filename:  tree.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/13/2021 09:00:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../include/tree.h"

/* PUBLIC */
static void print_tree(node_t *root);
static void free_all(tree_t *tree);

/* PRIVATE */
static void print(tree_t *tree);
void free_tree(node_t *root);
static void print_type(type_t type);

/*
 * PUBLIC
 */

static void free_all(tree_t *tree)
{
  free_tree(tree->root);
}

static void print(tree_t *tree)
{
  print_tree(tree->root);
}


void init_tree(tree_t *tree)
{
   tree->root = NULL;
   tree->print = print;
   tree->free_all = free_all;
}


/*
 * PRIVATE 
 */

static void print_type(type_t type)
{
 switch(type)
 {
  case NUMBER: 
     printf("Type: Number\n");
      break;
  case ADDITIVE_OPERATOR:
     printf("Type: Additive Operator\n");
      break;
  case MULTIPLICATION_OPERATOR:
     printf("Type: Mutiplication Operator\n");
      break;
   default: 
     printf("Type: Unknown type\n");
 }
}


static void print_tree(node_t *root)
{
   if(root == NULL)
      return;

   print_type(root->type);

   if(root->type == NUMBER)
     printf("%ld\n", root->value); 

   else
      printf("%c\n", (char)root->value);

   print_tree(root->left);
   print_tree(root->right);

}

void free_tree(node_t *root)
{
   if(root == NULL)
      return;

   free_tree(root->left);
   free_tree(root->right);

   free(root);
}


