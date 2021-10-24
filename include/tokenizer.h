#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum type {NUMBER, OPERAND}type_t;

typedef struct token{
  type_t type;
  long int value;

}token_t;

typedef struct tokenizer {
  char *str;
  int cursor;
  void (*load) (struct tokenizer*, char*);
  struct token* (*get_next_token) (struct tokenizer*); 
}tokenizer_t;


 void init_tokenizer(tokenizer_t *tokenizer);

#endif
