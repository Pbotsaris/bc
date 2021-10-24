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

   return create_node(token->value);

}


static node_t *numeric_literal(parser_t *parser, tokenizer_t *tokenizer)
{
   return eat(parser, tokenizer, NUMBER);

}


static node_t *program(parser_t *parser, tokenizer_t *tokenizer)
{
   return numeric_literal(parser, tokenizer);
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

