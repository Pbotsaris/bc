/*
 * =====================================================================================
 *
 *       Filename:  untils.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/18/2021 12:01:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../include/utils.h"

long int str_to_num(char *str)
{
   char *end;
   return strtol(str, &end, DECIMAL);
}

