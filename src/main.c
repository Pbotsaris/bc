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
 *         Author:  Pedro Botsaris 
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
   tokenizer_t  tokenizer;
   parser_t     parser;
   tree_t       ast;

   init_tokenizer(&tokenizer);
   init_parser(&parser);
   init_tree(&ast);

   ast.root = parser.parse(&parser, &tokenizer,"-(-((g-4)+-6))");
   
   if(ast.root == NULL)
      return 1;

   ast.eval(&ast);

   ast.free_all(&ast);
   tokenizer.free_str(&tokenizer);

   return 0;

}
