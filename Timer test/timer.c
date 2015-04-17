#include "armpmu_lib.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
  uint32_t time_start;
  uint32_t time_stop;
  int i;
  int r;
  int result;
  time_start = rdtsc32();
  for(i=0;i<10000;i++){
  r =  rand()%100;
  result = result *r;
	}
  time_stop = rdtsc32();
  printf("cycles: %i\n",time_stop-time_start);

return 0;  
}