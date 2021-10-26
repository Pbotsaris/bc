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
 //tree_t tree;
 //init_tree(&tree);
 //tree.add(&tree, 10);

 //tree.add(&tree, 3);
 //tree.add(&tree, 12);
 //tree.get_height(&tree);
 //tree.print(&tree);
 //tree.free_all(&tree);

 tokenizer_t tokenizer;
 parser_t parser;

 init_tokenizer(&tokenizer);
 init_parser(&parser);
 
node_t *node = parser.parse(&parser, &tokenizer,"10");

printf("node value: %d, type: %s\n", (char)node->value, node->type == NUMBER ? "Number": "Operator" );


// add -> call left + right
// negative(uniary) ->  - call self 
// integar -> return val
// if token is parentheses we can get_next_token again

 return 0;

}


// E EXPRESSION
// F FACTOR (-10 or !20) for example
// T TERM
// E -> T + E | T - E | T


//subtract, add, negative, divide, module, multiply
