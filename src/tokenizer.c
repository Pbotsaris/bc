/*
 * =====================================================================================
 *
 *       Filename:  tokenizer.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/17/2021 22:30:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "../include/tokenizer.h"
#include "../include/utils.h"

// +, -, *, /, and %

static int is_num(char c)
{
   return c >= '0' && c <= '9';
}

static int is_operator(char c)
{
return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

static int has_more_tokens(tokenizer_t *tokenizer)
{
   return tokenizer->cursor < (int)strlen(tokenizer->str); 
}


static token_t *do_num(tokenizer_t *tokenizer)
{
      token_t *token = (token_t*)malloc(sizeof(token_t));
      token->type = NUMBER;
      size_t len = strlen(tokenizer->str);
      char *buffer = (char*) malloc((len + 1) * sizeof(char));
       

      int count = 0;

      while(is_num(tokenizer->str[tokenizer->cursor]))
      {
         buffer[count] = tokenizer->str[tokenizer->cursor];
         tokenizer->cursor++;
         count++;
      }

      buffer[count] = '\0';
      token->value = str_to_num(buffer);

      free(buffer);
      return token;
}

static token_t *do_operator(tokenizer_t *tokenizer)
{
      token_t *token = (token_t*)malloc(sizeof(token_t));
      token->type = OPERATOR;
      token->value = (long int) tokenizer->str[tokenizer->cursor];
      tokenizer->cursor++;
      return token;
}

static token_t *get_next_token(tokenizer_t *tokenizer)
{
   if(!has_more_tokens(tokenizer))
   {
      printf("no more values\n");
      return NULL;
   }

   if(is_num(tokenizer->str[tokenizer->cursor]))
      return do_num(tokenizer);
   else if(is_operator(tokenizer->str[tokenizer->cursor]))
      return do_operator(tokenizer);

   return NULL;
}

static void load(tokenizer_t *tokenizer, char *str)
{
   size_t len = strlen(str);
   tokenizer->str = (char*) malloc((len +  1) * sizeof(char));

   strcpy(tokenizer->str, str);

   tokenizer->cursor = 0;
}


void init_tokenizer(tokenizer_t *tokenizer)
{
   tokenizer->load = load;
   tokenizer->get_next_token = get_next_token;
}
