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

/* PUBLIC */
static node_t *parse(parser_t *parser, tokenizer_t *tokenizer, char *str);

/* PRIVATE */
static node_t *create_node(long int value, type_t type);
static node_t *eat(parser_t *parser, tokenizer_t *tokenizer, type_t type);
static node_t *numeric_literal(parser_t *parser, tokenizer_t *tokenizer);
static node_t *parethesis_expression(parser_t *parser, tokenizer_t *tokenizer);
static node_t *primary_expression(parser_t *parser, tokenizer_t *tokenizer);
static node_t *multiplicative_expression(parser_t *parser, tokenizer_t *tokenizer);
static node_t *additive_expression(parser_t *parser, tokenizer_t *tokenizer);
static node_t *expression(parser_t *parser, tokenizer_t *tokenizer);
static node_t *program(parser_t *parser, tokenizer_t *tokenizer);

/*
 *   PUBLIC 
 */

void init_parser(parser_t *parser)
{
   parser->parse = parse;
}

/*
 *   PUBLIC METHOD
 */

static node_t *parse(parser_t *parser, tokenizer_t *tokenizer, char *str)
{
   tokenizer->load(tokenizer, str);
   parser->lookahead = tokenizer->get_next_token(tokenizer);

   return program(parser, tokenizer);
}

/*
 *   PRIVATE
 */

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

   // do not return node for parethesis
   if(type == PARENTHESIS)
      return NULL;

   return create_node(token->value, token->type);

}

static node_t *numeric_literal(parser_t *parser, tokenizer_t *tokenizer)
{
   return eat(parser, tokenizer, NUMBER);
}

static  node_t *parethesis_expression(parser_t *parser, tokenizer_t *tokenizer)
{
    // ignore return
     eat(parser, tokenizer, PARENTHESIS);
     node_t *exp = expression(parser, tokenizer);
    // eat closing parenthesis
      // TODO: ERROR HANDLING FOR CORRECT CLOSING PARETHESIS
     eat(parser, tokenizer, PARENTHESIS);

     return exp;
}

static node_t *primary_expression(parser_t *parser, tokenizer_t *tokenizer)
{
   if(parser->lookahead->type == PARENTHESIS)
       return parethesis_expression(parser, tokenizer);

    else
      return numeric_literal(parser, tokenizer);
}

static node_t *multiplicative_expression(parser_t *parser, tokenizer_t *tokenizer)
{
   node_t *left = primary_expression(parser, tokenizer);
   node_t *operator = NULL;
   node_t *right = NULL;

   while(parser->lookahead != NULL && parser->lookahead->type == MULTIPLICATION_OPERATOR)
   {
      operator = eat(parser, tokenizer, MULTIPLICATION_OPERATOR);
      right = primary_expression(parser, tokenizer);
      operator->left = left;
      operator->right = right;
      left = operator;
   }
   return left;
}

static node_t *additive_expression(parser_t *parser, tokenizer_t *tokenizer)
{
   node_t *left = multiplicative_expression(parser, tokenizer);
   node_t *operator = NULL;
   node_t *right = NULL;

   while(parser->lookahead != NULL && parser->lookahead->type == ADDITIVE_OPERATOR)
   {
      operator = eat(parser, tokenizer, ADDITIVE_OPERATOR);
      right = multiplicative_expression(parser, tokenizer);
      operator->left = left;
      operator->right = right;
      left = operator;
   }
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





