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
 *         Author:  Pedro Botsaris, 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "../include/tokenizer.h"
#include "../include/utils.h"


/* PUBLIC */
static void load(tokenizer_t *tokenizer, char *str);
static token_t *get_next_token(tokenizer_t *tokenizer);
static void free_str(tokenizer_t *tokenizer);

/* PRIVATE */
static int is_whitespace(char c);
static int is_additive(char c);
static int is_multiplication(char c);
static int is_num(char c);
static int is_parenthesis(char c);
static int is_valid(char c);
static int validate(char *str);
static int has_more_tokens(tokenizer_t *tokenizer);
static token_t *do_operator(tokenizer_t *tokenizer, type_t type);
static token_t *do_num(tokenizer_t *tokenizer);

/*
 * PUBLIC FUNCTION
 */

void init_tokenizer(tokenizer_t *tokenizer)
{
   tokenizer->load = load;
   tokenizer->get_next_token = get_next_token;
   tokenizer->free_str = free_str;
}

/*
 * PUBLIC METHODS
 */

static void load(tokenizer_t *tokenizer, char *str)
{
   size_t len = strlen(str);
   

   if(validate(str))
   {
       tokenizer->str = (char*) malloc((len +  1) * sizeof(char));
       strcpy(tokenizer->str, str);
   }
       
   else
      tokenizer->str = NULL;


   tokenizer->cursor = 0;
}

static token_t *get_next_token(tokenizer_t *tokenizer)
{

   if(!has_more_tokens(tokenizer))
      return NULL;

   if(is_num(tokenizer->str[tokenizer->cursor]))
      return do_num(tokenizer);

   else if(is_additive(tokenizer->str[tokenizer->cursor]))
      return do_operator(tokenizer, ADDITIVE_OPERATOR);

   else if(is_multiplication(tokenizer->str[tokenizer->cursor]))
      return do_operator(tokenizer, MULTIPLICATION_OPERATOR);

   else if(is_parenthesis(tokenizer->str[tokenizer->cursor]))
      return do_operator(tokenizer, PARENTHESIS);

   else if(is_whitespace(tokenizer->str[tokenizer->cursor]))
   {
      tokenizer->cursor++;
      return get_next_token(tokenizer);
   }
   
   return NULL;
}

static void free_str(tokenizer_t *tokenizer)
{
   free(tokenizer->str);
}

/*
 * PRIVATE
 */

static int is_whitespace(char c)     { return c == ' ' || c == '\t' || c == 10; }
static int is_additive(char c)       { return c == '+' || c == '-';}  
static int is_multiplication(char c) { return c == '/' || c == '*' || c == '%';}
static int is_num(char c)            { return c >= '0' && c <= '9'; }
static int is_parenthesis(char c)    { return c == '(' || c == ')' ; }

static int is_valid(char c)
{
return is_whitespace(c) || is_additive(c) || is_multiplication(c) ||  is_num(c) || is_parenthesis(c); 
}

static int validate(char *str)
{
   int i = 0;
   while(str[i] != '\0')
   {
      if(!is_valid(str[i]))
         return 0;

      i++;
   }
   return 1;
}

static int has_more_tokens(tokenizer_t *tokenizer)
{
   return tokenizer->cursor < (int)strlen(tokenizer->str); 
}

static token_t *do_operator(tokenizer_t *tokenizer, type_t type)
{
   token_t *token   = (token_t*)malloc(sizeof(token_t));
   token->type      = type;
   token->value     = (long int) tokenizer->str[tokenizer->cursor];

   tokenizer->cursor++;
   return token;
}

static token_t *do_num(tokenizer_t *tokenizer)
{
   token_t *token    = (token_t*)malloc(sizeof(token_t));
   token->type       = NUMBER;
   size_t len        = strlen(tokenizer->str);
   char *buffer      = (char*) malloc((len + 1) * sizeof(char));
   int count         = 0;

   while(is_num(tokenizer->str[tokenizer->cursor]))
   {
      buffer[count]  = tokenizer->str[tokenizer->cursor];
      tokenizer->cursor++; 
      count++;
   }

   buffer[count]      = '\0';
   token->value       = str_to_num(buffer);

   free(buffer);
   return token;
}

