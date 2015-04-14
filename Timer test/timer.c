#include "rpi_pmu.h"
#include <stdint.h>
#include <stdio.h>



int main(){
  uint64_t* cycles;
  uint64_t* evt0;
  uint64_t* evt1;
  start_counting(1, 1);
  stop_counting();
  get_counts(cycles, evt0, evt1);
  printf("cycles: %lli\n",cycles);
  printf("evt0: %lli\n",evt0);
  printf("evt1: %lli\n",evt1);
  

  
}