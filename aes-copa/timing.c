#include <stdio.h>
#include <string.h> /* memcpy() */
#include <stdint.h> /* uint32_t */
#include <stdlib.h>
#include <time.h>
#include <linux/kernel.h>
//#include <linux/module.h>


#include "encrypt.h"

#define BLOCKS 7
#define PERF_DEF_OPTS (1 | 16)


 #define TIMER_SAMPLE_CNT (10000)
static void
enable_cpu_counters(void* data)
{
        /* Enable user-mode access to counters. */
        asm volatile("mcr p15, 0, %0, c9, c14, 0" :: "r"(1));
        /* Program PMU and enable all counters */
        asm volatile("mcr p15, 0, %0, c9, c12, 0" :: "r"(PERF_DEF_OPTS));
        asm volatile("mcr p15, 0, %0, c9, c12, 1" :: "r"(0x8000000f));
}
 

static int __init
init(void)
{
        on_each_cpu(enable_cpu_counters, NULL, 1);
        printk(KERN_INFO "[" DRVR_NAME "] initialized");
        return 0;
}

static void __exit
fini(void)
{
        on_each_cpu(disable_cpu_counters, NULL, 1);
        printk(KERN_INFO "[" DRVR_NAME "] unloaded");
}

// static inline void init_perfcounters (int32_t do_reset, int32_t enable_divider)
// {
// //   /* enable user-mode access to the performance counter*/
// //   asm ("mcr p15, 0, %0, C9, C14, 0\n\t" :: "r"(1));
// // 
// //   /* disable counter overflow interrupts (just in case)*/
// //   asm ("mcr p15, 0, %0, C9, C14, 2\n\t" :: "r"(0x8000000f));
//   int32_t value = 1;
// 
//   // peform reset:  
//   if (do_reset)
//   {
//     value |= 2;     // reset all counters to zero.
//     value |= 4;     // reset cycle counter to zero.
//   } 
// 
//   if (enable_divider)
//     value |= 8;     // enable "by 64" divider for CCNT.
// 
//   value |= 16;
// 
//   // program the performance-counter control-register:
//   asm volatile ("mcr p15, 0, %0, c9, c12, 0\t\n" :: "r"(value));  
// 
//   // enable all counters:  
//   asm volatile ("mcr p15, 0, %0, c9, c12, 1\t\n" :: "r"(0x8000000f));  
// 
//   // clear overflows:
//   asm volatile ("mcr p15, 0, %0, c9, c12, 3\t\n" :: "r"(0x8000000f));
// }

static inline uint32_t
rdtsc32(void)
{
#if defined(__GNUC__) && defined(__ARM_ARCH_7A__)
        uint32_t r = 0;
        asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(r) );
        return r;
#else
#error Unsupported architecture/compiler!
#endif
}


int main() {

const unsigned char key[16] = {0x7f,0x7e,0x7d,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x70};
unsigned char nonce[16] = {0x09,0xf9,0x11,0x02,0x9d,0x74,0xe3,0x5b,0xd8,0x41,0x56,0xc5,0x63,0x56,0x88,0xc0};
unsigned char in[16*BLOCKS*100], out[16*BLOCKS*100], tag[16];

asm volatile ("mcr p15,  0, %0, c15,  c9, 0\n" : : "r" (1));
  int i, j, k, l=100;

  int initsucces = init()
  printf("init succes:%i\n", initsucces);
//  srand(time(NULL));
  for (i=0; i<16*BLOCKS*l; i++)
    in[i] = (unsigned char)rand();

 //  init_perfcounters(1,0);

   unsigned uint32_t overhead = rdtsc32();
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
  printf("Cycles for YAES: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/(16.0*BLOCKS*l));
  fini();

  return 0;
}

