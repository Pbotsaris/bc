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


static int max(int a, int b)
{
   return a >= b ? a : b;
}

static int node_height(node_t *root)
{
      return root == NULL ? -1 : root->height;
}

static node_t *create_node(node_t *node, long int value)
{
   node = (node_t*) malloc(sizeof(node_t));
   node->value = value;
   node->height = 0;
   node->left = NULL;
   node->right = NULL;

   return node;
}

static node_t *add_node(node_t *root, long int value)
{
   if(root == NULL)
      return create_node(root, value);

   if(value <= root->value)
      root->right = add_node(root->right, value);
   else
      root->left = add_node(root->left, value);

   root->height = 1 + max(node_height(root->left), node_height(root->right));  

   return root;

}


static int height(node_t *root)
{
   if(root == NULL)
      return 0;

   return 1 + max(height(root->left), height(root->right));
}


void print_tree(node_t *root)
{
   if(root == NULL)
      return;

     printf("%d\n", root->value); 

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

static void add(tree_t *tree, long int value)
{
   tree->root = add_node(tree->root, value);
}

static void get_height(tree_t *tree)
{
   tree->height = height(tree->root) - 1;
}


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
   tree->add = add;
   tree->get_height = get_height;
   tree->print = print;
   tree->free_all = free_all;
}







