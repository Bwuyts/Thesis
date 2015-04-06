#include <stdio.h>
#include <string.h> /* memcpy() */
#include <stdint.h> /* uint32_t */
#include <stdlib.h>
#include <time.h>
#include <linux/kernel.h>
// #include <linux/module.h>
// #include <linux/init.h>
// #include <linux/moduleparam.h>
// #include <linux/workqueue.h>
// #include <linux/time.h>
// #include <asm/mutex.h>

#include "encrypt.h"

#define BLOCKS 7

 #define TIMER_SAMPLE_CNT (10000)

static inline unsigned int get_cyclecount (void)
{
  unsigned int value;
  // Read CCNT Register
  asm volatile ("mrc p15, 0, %0, c9, c13, 0\t\n": "=r"(value));  
  return value;
}

static inline void init_perfcounters (int32_t do_reset, int32_t enable_divider)
{
  /* enable user-mode access to the performance counter*/
  asm ("mcr p15, 0, %0, C9, C14, 0\n\t" :: "r"(1));

  /* disable counter overflow interrupts (just in case)*/
  asm ("mcr p15, 0, %0, C9, C14, 2\n\t" :: "r"(0x8000000f));
  int32_t value = 1;

  // peform reset:  
  if (do_reset)
  {
    value |= 2;     // reset all counters to zero.
    value |= 4;     // reset cycle counter to zero.
  } 

  if (enable_divider)
    value |= 8;     // enable "by 64" divider for CCNT.

  value |= 16;

  // program the performance-counter control-register:
  asm volatile ("mcr p15, 0, %0, c9, c12, 0\t\n" :: "r"(value));  

  // enable all counters:  
  asm volatile ("mcr p15, 0, %0, c9, c12, 1\t\n" :: "r"(0x8000000f));  

  // clear overflows:
  asm volatile ("mcr p15, 0, %0, c9, c12, 3\t\n" :: "r"(0x8000000f));
}

int main() {

const unsigned char key[16] = {0x7f,0x7e,0x7d,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x70};
unsigned char nonce[16] = {0x09,0xf9,0x11,0x02,0x9d,0x74,0xe3,0x5b,0xd8,0x41,0x56,0xc5,0x63,0x56,0x88,0xc0};
unsigned char in[16*BLOCKS*100], out[16*BLOCKS*100], tag[16];

  int i, j, k, l=100;

//  srand(time(NULL));
  for (i=0; i<16*BLOCKS*l; i++)
    in[i] = (unsigned char)rand();

   init_perfcounters(1,0);

   unsigned int overhead = get_cyclecount();
   overhead = get_cyclecount() - overhead;   
  
  
 uint32_t t0,t1;
  
 uint32_t tMin = 0xFFFFFFFF;         /* big number to start */
  
  printf("Cycles for calibrate: %d\n", overhead);

  for (j=0;j<1000;j++) 
      crypto_aead_encrypt(out,tag,in,16*BLOCKS*100,0,0,0,nonce,key);


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = get_cyclecount();
      crypto_aead_encrypt(out,tag,in,16*BLOCKS*100,0,0,0,nonce,key);

    t1 = get_cyclecount();
    if (tMin > t1-t0 - overhead) tMin = t1-t0 - overhead;
  }
  printf("Cycles for YAES: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/(16.0*BLOCKS*l));
  

  return 0;
}

