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
 *         Author: Pedro Botsaris,
 *   Organization:
 *
 * =====================================================================================
 */

#include "../include/parser.h"
#include "../include/utils.h"

/* PUBLIC */
static node_t *parse(parser_t *parser, tokenizer_t *tokenizer, char *str);
static void validate(parser_t *parser);

/* PRIVATE */
static node_t *create_node(token_t *token);
static node_t *eat(parser_t *parser, tokenizer_t *tokenizer, type_t type);
static node_t *numeric_literal(parser_t *parser, tokenizer_t *tokenizer);
static node_t *binary_expression(parser_t *parser, tokenizer_t *tokenizer, func_ptr f, type_t type);
static node_t *parethesis_expression(parser_t *parser, tokenizer_t *tokenizer);
static node_t *primary_expression(parser_t *parser, tokenizer_t *tokenizer);
static node_t *multiplicative_expression(parser_t *parser, tokenizer_t *tokenizer);
static node_t *additive_expression(parser_t *parser, tokenizer_t *tokenizer);
static node_t *expression(parser_t *parser, tokenizer_t *tokenizer);
static node_t *program(parser_t *parser, tokenizer_t *tokenizer);

/*
 *   PUBLIC FUNCTION
 */

void init_parser(parser_t *parser)
{
    parser->parse       = parse;
    parser->validate    = validate;
    parser->valid       = 1;
}

/*
 *   PUBLIC METHOD
 */

static node_t *parse(parser_t *parser, tokenizer_t *tokenizer, char *str)
{
   
    tokenizer->load(tokenizer, str);

    if(tokenizer->str == NULL)
    {
        printf("Syntax Error: invalid Token\n");
        parser->valid = 0;
         parser->lookahead = NULL;
        return NULL; 
    }


    parser->lookahead = tokenizer->get_next_token(tokenizer);

    return program(parser, tokenizer);
}

static void validate(parser_t *parser)
{
    if(parser->lookahead != NULL)
    {
        printf("Syntax Error: Unexpected Token\n");
        parser->valid = 0;
        free(parser->lookahead);
    }  
}

/*
 *   PRIVATE
 */

static node_t *create_node(token_t *token)
{
    node_t *node        = (node_t *)malloc(sizeof(node_t));
    node->value         = token->value;
    node->left          = NULL;
    node->right         = NULL;
    node->type          = token->type;

    free(token);
    return node;
}

static node_t *eat(parser_t *parser, tokenizer_t *tokenizer, type_t type)
{
    token_t *token = parser->lookahead;

    if (token == NULL)
    {
        printf("Syntax Error: Unexpected end of input\n");
        parser->valid = 0;
        return NULL;
    }

    if (token->type != type)
    {
        printf("Syntax Error: Unexpected token\n");
        parser->valid = 0;
        return NULL;
    }

    parser->lookahead = tokenizer->get_next_token(tokenizer);

    /* do not return node when parethesis */
    if (type == PARENTHESIS)
    {
        free(token);
        return NULL;
    }

    return create_node(token);
}

static node_t *numeric_literal(parser_t *parser, tokenizer_t *tokenizer)
{
    return eat(parser, tokenizer, NUMBER);
}

static node_t *parethesis_expression(parser_t *parser, tokenizer_t *tokenizer)
{
    eat(parser, tokenizer, PARENTHESIS);
    node_t *exp = NULL;

    /*  no empty or unbalanced parenthesis  */
    if (parser->lookahead != NULL && parser->lookahead->value != ')') 
        exp = expression(parser, tokenizer);
    else 
        parser->valid = 0;

    eat(parser, tokenizer, PARENTHESIS);

    return exp;
}

static node_t *primary_expression(parser_t *parser, tokenizer_t *tokenizer)
{
    if (parser->lookahead->type == PARENTHESIS)
        return parethesis_expression(parser, tokenizer);

    else
        return numeric_literal(parser, tokenizer);
}

static node_t *unary_expression(parser_t *parser, tokenizer_t *tokenizer)
{
    node_t *operator         = NULL;

    if(parser->lookahead == NULL)
    {
        printf("Syntax Error: Unexpected end of input\n");
        parser->valid = 0;
        return NULL;
    }

    if (parser->lookahead->type == ADDITIVE_OPERATOR)
        operator= eat(parser, tokenizer, ADDITIVE_OPERATOR);

    if (operator!= NULL)
    {
        operator->type       = UNARY_OPERATOR;
        operator->left       = unary_expression(parser, tokenizer);
        return operator;
    }

    return primary_expression(parser, tokenizer);
}

static node_t *binary_expression(parser_t *parser, tokenizer_t *tokenizer, func_ptr f, type_t type)
{
    node_t *left            = f(parser, tokenizer);
    node_t *operator        = NULL;
    node_t *right           = NULL;

    while (parser->lookahead != NULL && parser->lookahead->type == type)
    {
        operator            = eat(parser, tokenizer, type);
        right               = f(parser, tokenizer);
        // root
        operator->left      = left;
        operator->right     = right;
        left = operator;
    }
    return left;
}

static node_t *multiplicative_expression(parser_t *parser, tokenizer_t *tokenizer)
{
    return binary_expression(parser, tokenizer, unary_expression, MULTIPLICATION_OPERATOR);
}

static node_t *additive_expression(parser_t *parser, tokenizer_t *tokenizer)
{
    return binary_expression(parser, tokenizer, multiplicative_expression, ADDITIVE_OPERATOR);
}

static node_t *expression(parser_t *parser, tokenizer_t *tokenizer)
{
    return additive_expression(parser, tokenizer);
}
static node_t *program(parser_t *parser, tokenizer_t *tokenizer)
{
    return expression(parser, tokenizer);
}
