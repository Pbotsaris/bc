/*
 * =====================================================================================
 *
 *       Filename:  parser.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/18/2021 09:12:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef PARSER_H
#define PARSER_H
#include "../include/tree.h"
#include "../include/tokenizer.h"

typedef struct parser{
  char *lookahead;
  node_t * (*parse) (char*);
}parser_t;

void init_parser(parser_t *parser);

#endif


