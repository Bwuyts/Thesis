#include <stdio.h>
#include <string.h> /* memcpy() */
#include <stdint.h> /* uint32_t */
#include <stdlib.h>
#include <time.h>
#include "enable_arm_pmu2/armpmu_lib.h"


#include "encrypt.h"

#define BLOCKS 1

 #define TIMER_SAMPLE_CNT (10000)

int main() {

const unsigned char key[16] = {0x7f,0x7e,0x7d,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x70};
unsigned char nonce[16] = {0x09,0xf9,0x11,0x02,0x9d,0x74,0xe3,0x5b,0xd8,0x41,0x56,0xc5,0x63,0x56,0x88,0xc0};
unsigned char in[16*BLOCKS*256], out[16*BLOCKS*256];
unsigned long long tag[16];

//asm volatile ("mcr p15,  0, %0, c15,  c9, 0\n" : : "r" (1));
  int i, j, k, l=100;

//  srand(time(NULL));
  for (i=0; i<16*BLOCKS*l; i++)
    in[i] = (unsigned char)rand();

   uint32_t overhead = rdtsc32();
   overhead = rdtsc32() - overhead;   
  
  
 uint32_t t0,t1;
  
 uint32_t tMin = 0xFFFFFFFF;         /* big number to start */
  
  printf("Cycles for calibrate: %d\n", overhead);

  for (j=0;j<1000;j++) 
      crypto_aead_encrypt(out,tag,in,16*BLOCKS*100,0,0,0,nonce,key);


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = rdtsc32();
      crypto_aead_encrypt(out,tag,in,16*BLOCKS*100,0,0,0,nonce,key);

    t1 = rdtsc32();
    if (tMin > t1-t0 - overhead) tMin = t1-t0 - overhead;
  }
  printf("Cycles for AES-copa: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/(16.0*BLOCKS*l));
  return 0;
}

