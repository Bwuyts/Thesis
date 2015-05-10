#include "wmmintrin.h" 
#include "smmintrin.h"
#ifndef __PRINT_H
#define __PRINT_H

void printchar(unsigned char* toPrint,int printLength, char* message);
void printvector(__m128i toPrint, char* message);

#endif
