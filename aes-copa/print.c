#include <stdio.h>
void printchar(unsigned char* toPrint,int printLength, char* message);

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
