/*
 * =====================================================================================
 *
 *       Filename:  parser.c
 *
 *    Description 
 *
 *        Version:  1.0
 *        Created:  10/18/2021 09:12:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "../include/parser.h"
#include "../include/utils.h"


static node_t *create_node(long int value)
{
   node_t *node = (node_t*) malloc(sizeof(node_t));
   node->value = value;
   node->height = 0;
   node->left = NULL;
   node->right = NULL;
   node->type = NUMERIC_LITERAL;

   return node;
}

static node_t *numeric_literal(char *str)
{
   long int num = str_to_num(str);

   return create_node(num);

}



 static node_t *program(char *str)
{
    return numeric_literal(str);
}


static node_t *parse(char *str)
{
   return program(str);
}


//static void eat (parser_t parser, type_t type) 
//{
//   
//
//}

void init_parser(parser_t *parser)
{
   parser->parse = parse;
}

