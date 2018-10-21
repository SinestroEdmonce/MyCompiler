#ifndef __COMMON_H_
#define __COMMON_H_

#include<string.h>
#include<stdlib.h>
#include<assert.h>

/* transform the string to int or float */
int Oct_2_Dec(char* src);
int Hex_2_Dec(char* src);
float FloatExp_2_FloatCommon(char* src);

#endif