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
 tree_t tree;
 init_tree(&tree);
 tree.add(&tree, 10);

 tree.add(&tree, 3);
 tree.add(&tree, 12);
 tree.get_height(&tree);
 tree.print(&tree);
 tree.free_all(&tree);

 tokenizer_t tokenizer;

 init_tokenizer(&tokenizer);
 tokenizer.load(&tokenizer, "12*34");
 printf("b4 cursor: %d\n", tokenizer.cursor);
 token_t *token = tokenizer.get_next_token(&tokenizer);
 printf("from token: %ld, cursor: %d\n", token->value, tokenizer.cursor);
 if(token->type == NUMBER)
    printf("token type: Number\n");

 token = tokenizer.get_next_token(&tokenizer);
 printf("from token: %c\n", (char)token->value);



 //token = tokenizer.get_next_token(&tokenizer);
 //printf("from token2: %s cursor: %d\n", token->value, tokenizer.cursor);

 //token = tokenizer.get_next_token(&tokenizer);
 //printf("from token2: %s cursor: %d\n", token->value, tokenizer.cursor);

 parser_t parser;
 init_parser(&parser);
 
node_t *node = parser.parse("10");

printf("node value: %ld\n", node->value);

 return 0;

}

