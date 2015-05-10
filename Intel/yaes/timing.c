#include <stdio.h>
#include <string.h> /* memcpy() */
#include <stdint.h> /* uint32_t */
#include <stdlib.h>
#include <time.h>

#include <x86intrin.h>
#include "yaes.h"

#define BLOCKS 8
#define HIRES

#ifdef HIRES
/************** Timing routine (for performance measurements) ***********/
/* By Doug Whiting */
/* unfortunately, this is generally assembly code and not very portable */
#if defined(_M_IX86) || defined(__i386) || defined(_i386) || defined(__i386__) || defined(i386) || \
    defined(_X86_)   || defined(__x86_64__) || defined(_M_X64) || defined(__x86_64)
#define _Is_X86_    1
#endif

#if  defined(_Is_X86_) && (!defined(__STRICT_ANSI__)) && (defined(__GNUC__) || !defined(__STDC__)) && \
    (defined(__BORLANDC__) || defined(_MSC_VER) || defined(__MINGW_H) || defined(__GNUC__))
#define HI_RES_CLK_OK         1          /* it's ok to use RDTSC opcode */

#if defined(_MSC_VER) // && defined(_M_X64)
#include <intrin.h>
#pragma intrinsic(__rdtsc)         /* use MSVC rdtsc call where defined */
#endif

#endif

uint32_t HiResTime(void)           /* return the current value of time stamp counter */
    {
#if defined(HI_RES_CLK_OK)
    uint32_t x[2];
#if   defined(__BORLANDC__)
#define COMPILER_ID "BCC"
    __emit__(0x0F,0x31);           /* RDTSC instruction */
    _asm { mov x[0],eax };
#elif defined(_MSC_VER)
#define COMPILER_ID "MSC"
#if defined(_MSC_VER) // && defined(_M_X64)
    x[0] = (uint32_t) __rdtsc();
#else
    _asm { _emit 0fh }; _asm { _emit 031h };
    _asm { mov x[0],eax };
#endif
#elif defined(__MINGW_H) || defined(__GNUC__)
#define COMPILER_ID "GCC"
    asm volatile("rdtsc" : "=a"(x[0]), "=d"(x[1]));
#else
#error  "HI_RES_CLK_OK -- but no assembler code for this platform (?)"
#endif
    return x[0];
#else
    /* avoid annoying MSVC 9.0 compiler warning #4720 in ANSI mode! */
#if (!defined(_MSC_VER)) || (!defined(__STDC__)) || (_MSC_VER < 1300)
    FatalError("No support for RDTSC on this CPU platform\n");
#endif
    return 0;
#endif /* defined(HI_RES_CLK_OK) */
    }

#define ALIGN __attribute__ ((aligned(32)))    

#define TIMER_SAMPLE_CNT (10000)

uint32_t calibrate()
{
    uint32_t dtMin = 0xFFFFFFFF;        /* big number to start */
    uint32_t t0,t1,i;

    for (i=0;i < TIMER_SAMPLE_CNT;i++)  /* calibrate the overhead for measuring time */
        {
        t0 = HiResTime();
        t1 = HiResTime();
        if (dtMin > t1-t0)              /* keep only the minimum time */
            dtMin = t1-t0;
        }
    return dtMin;
}
#else
#define ALIGN
#endif


int main() {

const unsigned char key[16] = {0x7f,0x7e,0x7d,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x70};
unsigned char nonce[16] = {0x09,0xf9,0x11,0x02,0x9d,0x74,0xe3,0x5b,0xd8,0x41,0x56,0xc5,0x63,0x56,0x88,0xc0};
unsigned char in[4096], out[4096], adata[4096], tag[16];

  int i, j, k, l=100;

  srand(time(NULL));
  for (i=0; i<4096; i++){
    in[i] = (unsigned char)rand();
    adata[i]=(unsigned char)rand();}
    
#if 0
  for (i=0; i!=128*l; i++) {
    printf("%02x ",in[i]);
  }
  for (i=0; i!=16; i++) {
    printf("%02x ",key[i]);
  }
  printf("\n");
#endif
 
#ifdef HIRES
  uint32_t t0,t1;
  
  uint32_t tMin = 0xFFFFFFFF;         /* big number to start */
  
  uint32_t dtMin = calibrate();
  printf("Cycles for calibrate: %d\n", dtMin);

  for (j=0;j<1000;j++) 
      //void YAES128_ENC(const unsigned char* K,const unsigned char *N, const unsigned char *A, unsigned char *M, unsigned char *C, unsigned char *T, int Tau, int lengthM, int lengthA, int lengthN);
     YAES128_ENC(key,nonce, 0, in, out, tag, 16, 16*BLOCKS*l, 0, 16);

  printf("without adata");
  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

     YAES128_ENC(key,nonce, 0, in, out, tag, 16, 64, 0, 16);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for YAES 64: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/(1*BLOCKS));
#endif
  
#ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

     YAES128_ENC(key,nonce, 0, in, out, tag, 16, 128, 0, 16);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for YAES 128: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/(2*BLOCKS));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

     YAES128_ENC(key,nonce, 0, in, out, tag, 16, 256, 0, 16);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for YAES 256: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/(4*BLOCKS));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

     YAES128_ENC(key,nonce, 0, in, out, tag, 16, 512, 0, 16);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for YAES 512: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/(8*BLOCKS));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

     YAES128_ENC(key,nonce, 0, in, out, tag, 16, 1024, 0, 16);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for YAES 1024: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/(32*BLOCKS));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

     YAES128_ENC(key,nonce, 0, in, out, tag, 16, 2048, 0, 16);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for YAES 2048: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/(64*BLOCKS));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

     YAES128_ENC(key,nonce, 0, in, out, tag, 16, 16*BLOCKS*l, 0, 16);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for YAES 4096: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/(128*BLOCKS));
#endif
  
  
#if 0
  for (i=0; i!=128; i++) {
    printf("%02x ",out[i]);
  }
  printf("\n");
#endif
  return 0;
}

