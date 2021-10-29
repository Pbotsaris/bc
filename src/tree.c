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
 *         Author:  Pedro Botsaris, 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../include/tree.h"

/* PUBLIC */
static void print_tree(node_t *root);
static void free_all(tree_t *tree);
static long eval(tree_t *tree);

/* PRIVATE */
static void print(tree_t *tree);
static void free_tree(node_t *root);
static void print_type(type_t type);
static long evaluate(node_t *root, long result);


/* PRIVATE HELPERS */

static long mult_div(node_t *root);
static long add_sub(node_t *root);
static long unary(node_t *root);
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

static long eval(tree_t *tree)
{
   return evaluate(tree->root, 0);
}


void init_tree(tree_t *tree)
{
   tree->root       = NULL;
   tree->print      = print;
   tree->free_all   = free_all;
   tree->eval       = eval;
}

static long evaluate(node_t *root, long result)
{
 if(root == NULL)
      return 0;

   evaluate(root->left, result);
   evaluate(root->right, result);

   if(root->type == MULTIPLICATION_OPERATOR)
     root->value = mult_div(root);

   if(root->type == ADDITIVE_OPERATOR)
      root->value = add_sub(root);

    if(root->type == UNARY_OPERATOR)
     root->value = unary(root);

    return root->value;
}

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
  case UNARY_OPERATOR:
     printf("Type: Unary Operator\n");
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


static void free_tree(node_t *root)
{
   if(root == NULL)
      return;

   free_tree(root->left);
   free_tree(root->right);

   free(root);
}


/*
 * PRIVATE HELPERS
 */

static long mult_div(node_t *root)
{
   if(root->value == '*')
       return root->left->value * root->right->value;
   if(root->value == '/')
       return root->left->value / root->right->value;
   else
       return root->left->value % root->right->value;
}

static long add_sub(node_t *root)
{
   if(root->value == '+')
       return root->left->value + root->right->value;
   else
       return root->left->value - root->right->value;
}


static long unary(node_t *root)
{
   if(root->value == '-')
      return root->left->value * -1;  /* unary value always on left */
   else
      return root->left->value;
}






