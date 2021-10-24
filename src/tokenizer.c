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


static int is_num(char c)
{
   return c >= '0' && c <= '9';
}

static int has_more_tokens(tokenizer_t *tokenizer)
{
   return tokenizer->cursor < (int)strlen(tokenizer->str); 
}

static void load(tokenizer_t *tokenizer, char *str)
{
   size_t len = strlen(str);
   tokenizer->str = (char*) malloc((len +  1) * sizeof(char));

   strcpy(tokenizer->str, str);
   tokenizer->cursor = 0;
}


static token_t *get_next_token(tokenizer_t *tokenizer)
{
   if(!has_more_tokens(tokenizer))
   {
      printf("no more values\n");
      return NULL;
   }

   if(is_num(tokenizer->str[0]))
   {
      token_t *token = (token_t*)malloc(sizeof(token_t));
      token->type = NUMBER;
      char *buffer = (char*) malloc(strlen((tokenizer->str) + 1) * sizeof(char));

      int count = 0;

      while(is_num(tokenizer->str[tokenizer->cursor]))
      {
         buffer[count] = tokenizer->str[tokenizer->cursor];
         tokenizer->cursor++;
         count++;
      }
      // free string in the tokenizer.
      // free(tokenizer->str);
      buffer[count] = '\0';
      token->value = str_to_num(buffer);

      free(buffer);
      return token;

   }
   return NULL;
}


void init_tokenizer(tokenizer_t *tokenizer)
{
   tokenizer->load = load;
   tokenizer->get_next_token = get_next_token;
}
