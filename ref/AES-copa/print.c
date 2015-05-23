#include <stdio.h>
#include "wmmintrin.h"
#include "smmintrin.h"
void printchar(unsigned char* toPrint,int printLength, char* message);
void printvector(__m128i toPrint, char* message);

void printchar(unsigned char* toPrint,int printLength, char* message){
  int i;
   printf("%s:\n",message);
   
  for(i=0;i<printLength/2;i++){
	printf("%02x%02x ",toPrint[2*i],toPrint[2*i+1]);
  }


if(printLength%2 ==1){
  printf("%02x ",toPrint[printLength-1]);
}
      printf("\n");
}
void printvector(__m128i toPrint, char* message){
    printf("%s:\n",message);
    unsigned char *val = (unsigned char*) &toPrint;//can also use uint32_t instead of 16_t
    printf("%02x%02x %02x%02x %02x%02x %02x%02x %02x%02x %02x%02x %02x%02x %02x%02x \n", 
           val[0], val[1], val[2], val[3],val[4], val[5], val[6], val[7],val[8], val[9], val[10], val[11],val[12], val[13], val[14], val[15]);
}
