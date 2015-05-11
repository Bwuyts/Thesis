#include <stdio.h>
#include <string.h> /* memcpy() */
#include <stdint.h> /* uint32_t */
#include <stdlib.h>
#include <time.h>

#include <x86intrin.h>
#include "aescopa.h"

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

  int i, j, k;

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
      //void silc-AES128_ENC(const unsigned char* K,const unsigned char *N, const unsigned char *A, unsigned char *M, unsigned char *C, unsigned char *T, int Tau, int lengthM, int lengthA, int lengthN);
	AES_COPA_encrypt(in,4096, adata, 0, nonce, 16, out, tag , key);

  printf("Without adata:\n\n");
  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_encrypt(in,64, adata, 0, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 64: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(64)));
#endif
  
#ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_encrypt(in,128, adata, 0, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 128: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(128)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_encrypt(in,256, adata, 0, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 256: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(256)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_encrypt(in,512, adata, 0, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 512: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(512)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  
  #ifdef HIRES

  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_encrypt(in,1024, adata, 0, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 1024: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(1024)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_encrypt(in,2048, adata, 0, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 2048: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(2048)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_encrypt(in,4096, adata, 0, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 4096: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(4096)));
#endif
    printf("With adata, same size:\n\n");
  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_encrypt(in,64, adata, 64, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 64: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(64)));
#endif
  
#ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_encrypt(in,128, adata, 128, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 128: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(128)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_encrypt(in,256, adata, 256, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 256: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(256)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_encrypt(in,512, adata, 512, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 512: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(512)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_encrypt(in,1024, adata, 1024, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 1024: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(1024)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_encrypt(in,2048, adata, 2048, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 2048: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(2048)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_encrypt(in,4096, adata, 4096, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 4096: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(4096)));
#endif
  #ifdef HIRES

      printf("\n\n\n\nDecryption:\n\n");

    printf("Without adata:\n\n");
  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_decrypt(in,64, adata, 0, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 64: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(64)));
#endif
  
#ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_decrypt(in,128, adata, 0, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 128: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(128)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_decrypt(in,256, adata, 0, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 256: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(256)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_decrypt(in,512, adata, 0, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 512: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(512)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  
  #ifdef HIRES

  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_decrypt(in,1024, adata, 0, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 1024: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(1024)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_decrypt(in,2048, adata, 0, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 2048: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(2048)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_decrypt(in,4096, adata, 0, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 4096: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(4096)));
#endif
    printf("With adata, same size:\n\n");
  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_decrypt(in,64, adata, 64, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 64: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(64)));
#endif
  
#ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_decrypt(in,128, adata, 128, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 128: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(128)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_decrypt(in,256, adata, 256, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 256: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(256)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_decrypt(in,512, adata, 512, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 512: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(512)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_decrypt(in,1024, adata, 1024, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 1024: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(1024)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_decrypt(in,2048, adata, 2048, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 2048: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(2048)));
#endif
  
  #ifdef HIRES
    
  tMin = 0xFFFFFFFF;         /* big number to start */
  


  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = HiResTime();
#endif

	AES_COPA_decrypt(in,4096, adata, 4096, nonce, 16, out, tag , key);

#ifdef HIRES
    t1 = HiResTime();
    if (tMin > t1-t0 - dtMin) tMin = t1-t0 - dtMin;
  }
#endif
  
#ifdef HIRES
  printf("Cycles for AES-Copa 4096: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/((double)(4096)));
#endif
  
#if 0
  for (i=0; i!=128; i++) {
    printf("%02x ",out[i]);
  }
  printf("\n");
#endif
  return 0;
}

