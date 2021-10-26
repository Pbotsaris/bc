/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  10/13/2021 08:56:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Pedro Botsaris, 
 *         
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "../include/tree.h"
#include "../include/tokenizer.h"
#include "../include/parser.h"

int main(void)
{

 
 tokenizer_t tokenizer;
 parser_t parser;
 tree_t ast;

 init_tokenizer(&tokenizer);
 init_parser(&parser);
 
/*
 *
   TEMP TEST BELOW:
  
 */

ast.root = parser.parse(&parser, &tokenizer,"(10+2)*10");

//printf("right->left %ld\n", node->right->left->value);
//printf("right->right %ld\n", node->right->right->value);


/*
 *
   IMPLEMENTED THIS TREE WHEN FIRST STARTED THE PROJECT BUT NOT USING IT. 

 tree_t tree;
 init_tree(&tree);
 tree.add(&tree, 10);
 tree.add(&tree, 3);
 tree.add(&tree, 12);
 tree.get_height(&tree);
 tree.print(&tree);
 tree.free_all(&tree);
*/

 return 0;

}


// E EXPRESSION
// F FACTOR (-10 or !20) for example
// T TERM
// E -> T + E | T - E | T


//subtract, add, negative, divide, module, multiply
