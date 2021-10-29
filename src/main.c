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

/* E -> T + E | T - E | T */

int main(void)
{

 tokenizer_t  tokenizer;
 parser_t     parser;
 tree_t       ast;

 init_tokenizer(&tokenizer);
 init_parser(&parser);
 init_tree(&ast);
 
/*
 *
   TEMP TEST BELOW:
  
 */

ast.root = parser.parse(&parser, &tokenizer,"-(-((-4)+-6))");
ast.print(&ast);
long result = ast.eval(&ast);
printf("RESULT: %ld\n", result);
ast.free_all(&ast);

 return 0;

}
