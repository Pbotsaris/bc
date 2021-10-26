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

static node_t *create_node(long int value, type_t type)
{
   node_t *node = (node_t*) malloc(sizeof(node_t));
   node->value = value;
   node->height = 0;
   node->left = NULL;
   node->right = NULL;
   node->type = type;

   return node;
}

static node_t *eat(parser_t *parser, tokenizer_t *tokenizer, type_t type) 
{
   token_t *token = parser->lookahead;

   if(token == NULL)
   {
      printf("Unexpected end of input.\n");// add token type here
      return NULL;
   }

   if(token->type != type)
   {
      printf("Unexpected token.\n"); // add error, token types
      return NULL;
   }

   // advance to next token
   parser->lookahead = tokenizer->get_next_token(tokenizer);

   return create_node(token->value, token->type);

}


static node_t *numeric_literal(parser_t *parser, tokenizer_t *tokenizer)
{
   return eat(parser, tokenizer, NUMBER);

}

//static node_t *operator(parser_t *parser, tokenizer_t *tokenizer)
//{
//   return eat(parser, tokenizer, OPERATOR);
//}

static node_t *additive_expression(parser_t *parser, tokenizer_t *tokenizer)
{
   node_t *left = numeric_literal(parser, tokenizer);
   node_t *operator = NULL;
   node_t *right = NULL;

   while(parser->lookahead->type == ADDITIVE_OPERATOR)
   {
     operator = eat(parser, tokenizer, ADDITIVE_OPERATOR);
     right = numeric_literal(parser, tokenizer);
   }

   if(operator != NULL)
   {
      operator->left = left;
      operator->right = right;
      return operator;
   }
   else
    // return literal if no operator
     return left;
}


static node_t *expression(parser_t *parser, tokenizer_t *tokenizer)
{
return additive_expression(parser, tokenizer);
}


static node_t *program(parser_t *parser, tokenizer_t *tokenizer)
{
   return expression(parser, tokenizer);
}


static node_t *parse(parser_t *parser, tokenizer_t *tokenizer, char *str)
{
   tokenizer->load(tokenizer, str);
   parser->lookahead = tokenizer->get_next_token(tokenizer);

   return program(parser, tokenizer);
}


void init_parser(parser_t *parser)
{
   parser->parse = parse;
}

