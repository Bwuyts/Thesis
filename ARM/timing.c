#include <stdio.h>
#include <string.h> /* memcpy() */
#include <stdint.h> /* uint32_t */
#include <stdlib.h>
#include <time.h>

//#include <x86intrin.h>
#include "encrypt.h"

#define BLOCKS 7
// #define HIRES
// 
// #ifdef HIRES
// /************** Timing routine (for performance measurements) ***********/
// /* By Doug Whiting */
// /* unfortunately, this is generally assembly code and not very portable */
// #if defined(_M_IX86) || defined(__i386) || defined(_i386) || defined(__i386__) || defined(i386) || \
//     defined(_X86_)   || defined(__x86_64__) || defined(_M_X64) || defined(__x86_64)
// #define _Is_X86_    1
// #endif
// 
// #if  defined(_Is_X86_) && (!defined(__STRICT_ANSI__)) && (defined(__GNUC__) || !defined(__STDC__)) && \
//     (defined(__BORLANDC__) || defined(_MSC_VER) || defined(__MINGW_H) || defined(__GNUC__))
// #define HI_RES_CLK_OK         1          /* it's ok to use RDTSC opcode */
// 
// #if defined(_MSC_VER) // && defined(_M_X64)
// #include <intrin.h>
// #pragma intrinsic(__rdtsc)         /* use MSVC rdtsc call where defined */
// #endif
// 
// #endif
// 
// uint32_t HiResTime(void)           /* return the current value of time stamp counter */
//     {
// #if defined(HI_RES_CLK_OK)
//     uint32_t x[2];
// #if   defined(__BORLANDC__)
// #define COMPILER_ID "BCC"
//     __emit__(0x0F,0x31);           /* RDTSC instruction */
//     _asm { mov x[0],eax };
// #elif defined(_MSC_VER)
// #define COMPILER_ID "MSC"
// #if defined(_MSC_VER) // && defined(_M_X64)
// #else    x[0] = (uint32_t) __rdtsc();
// 
//     _asm { _emit 0fh }; _asm { _emit 031h };
//     _asm { mov x[0],eax };
// #endif
// #elif defined(__MINGW_H) || defined(__GNUC__)
// #define COMPILER_ID "GCC"
//     asm volatile("rdtsc" : "=a"(x[0]), "=d"(x[1]));
// #else
// #error  "HI_RES_CLK_OK -- but no assembler code for this platform (?)"
// #endif
//     return x[0];
// #else
//     /* avoid annoying MSVC 9.0 compiler warning #4720 in ANSI mode! */
// #if (!defined(_MSC_VER)) || (!defined(__STDC__)) || (_MSC_VER < 1300)
//     FatalError("No support for RDTSC on this CPU platform\n");
// #endif
//     return 0;
// #endif /* defined(HI_RES_CLK_OK) */
//     }
// 
// #define ALIGN __attribute__ ((aligned(32)))    
// 
 #define TIMER_SAMPLE_CNT (10000)
// 
// uint32_t calibrate()
// {
//     uint32_t dtMin = 0xFFFFFFFF;        /* big number to start */
//     uint32_t t0,t1,i;
// 
//     for (i=0;i < TIMER_SAMPLE_CNT;i++)  /* calibrate the overhead for measuring time */
//         {
//         t0 = HiResTime();
//         t1 = HiResTime();
//         if (dtMin > t1-t0)              /* keep only the minimum time */
//             dtMin = t1-t0;
//         }
//     return dtMin;
// }
// #else
// #define ALIGN
// #endif
static inline unsigned int get_cyclecount (void)
{
  unsigned int value;
  // Read CCNT Register
  asm volatile ("MRC p15, 0, %0, c9, c13, 0\t\n": "=r"(value));  
  return value;
}

static inline void init_perfcounters (int32_t do_reset, int32_t enable_divider)
{
  // in general enable all counters (including cycle counter)
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
  asm volatile ("MCR p15, 0, %0, c9, c12, 0\t\n" :: "r"(value));  

  // enable all counters:  
  asm volatile ("MCR p15, 0, %0, c9, c12, 1\t\n" :: "r"(0x8000000f));  

  // clear overflows:
  asm volatile ("MCR p15, 0, %0, c9, c12, 3\t\n" :: "r"(0x8000000f));
}

int main() {

const unsigned char key[16] = {0x7f,0x7e,0x7d,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x70};
unsigned char nonce[16] = {0x09,0xf9,0x11,0x02,0x9d,0x74,0xe3,0x5b,0xd8,0x41,0x56,0xc5,0x63,0x56,0x88,0xc0};
unsigned char in[16*BLOCKS*100], out[16*BLOCKS*100], tag[16];

  int i, j, k, l=100;

  srand(time(NULL));
  for (i=0; i<16*BLOCKS*l; i++)
    in[i] = (unsigned char)rand();

  
    unsigned int overhead = get_cyclecount();
    overhead = get_cyclecount() - overhead;   
  
// #ifdef HIRES
  
  init_perfcounters(1,0);
  uint32_t t0,t1;
  
  uint32_t tMin = 0xFFFFFFFF;         /* big number to start */
  
  printf("Cycles for calibrate: %d\n", overhead);

  for (j=0;j<1000;j++) 
      crypto_aead_encrypt(out,tag,in,16*BLOCKS*100,0,0,0,nonce,key);


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = get_cyclecount();
// #endif
      crypto_aead_encrypt(out,tag,in,16*BLOCKS*100,0,0,0,nonce,key);

// #ifdef HIRES
    t1 = get_cyclecount();
    if (tMin > t1-t0 - overhead) tMin = t1-t0 - overhead;
  }
// #endif
  
// #ifdef HIRES
  printf("Cycles for YAES: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/(16.0*BLOCKS*l));
// #endif
  

  return 0;
}
