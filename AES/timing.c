#include <stdio.h>
#include <string.h> /* memcpy() */
#include <stdint.h> /* uint32_t */
#include <stdlib.h>
#include <time.h>
#include "enable_arm_pmu2/armpmu_lib.h"


#include "aes.h"

#define BLOCKS 1

 #define TIMER_SAMPLE_CNT (10000)

int main() {

const unsigned char key[16] = {0x7f,0x7e,0x7d,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x70};
unsigned char in[4096], out[4096], outd[4096];
 unsigned char* inp = in;
 unsigned char* outp = out;
//asm volatile ("mcr p15,  0, %0, c15,  c9, 0\n" : : "r" (1));
  int i, j, k, l=100;

//  srand(time(NULL));
  for (i=0; i<16*BLOCKS*l; i++)
    in[i] = (unsigned char)rand();

   uint32_t overhead = rdtsc32();
   overhead = rdtsc32() - overhead; 
  
   printf("Cycles for calibrate: %d\n", overhead);

  
   uint32_t t0,t1;
        /* big number to start */
    uint32_t tMin = 0xFFFFFFFF;   
  
        AES_KEY expkeyp;
        AES_KEY* expkey = &expkeyp;
        AES_KEY expkeydp;
        AES_KEY* expkeyd = &expkeydp;
    for (k=0;k < 1000;k++)        
        AES_set_encrypt_key(key,128,expkey);
        
    for (k=0;k < TIMER_SAMPLE_CNT;k++) {
            t0 = rdtsc32();
            AES_set_encrypt_key(key,128,expkey);
            t1 = rdtsc32();
    if (tMin > t1-t0 - overhead) tMin = t1-t0 - overhead;
  }
  
    printf("Cycles for AES encryption key expansion: %d\n", tMin);
      tMin = 0xFFFFFFFF

    for (k=0;k < 1000;k++)        
        AES_set_decrypt_key(key,128,expkeyd);
       for (k=0;k < TIMER_SAMPLE_CNT;k++) {
            t0 = rdtsc32();
            AES_set_decrypt_key(key,128,expkeyd);
            t1 = rdtsc32();
    if (tMin > t1-t0 - overhead) tMin = t1-t0 - overhead;
  }     
  printf("Cycles for AES decryption key expansion: %d\n", tMin);
    tMin = 0xFFFFFFFF

    for (j=0;j<1000;j++) {
        AES_encrypt(in, out,expkey);
        
    }
  for (k=0;k < TIMER_SAMPLE_CNT;k++) {
    t0 = rdtsc32();
    for(i=0;i<256;i= i + 16){
        AES_encrypt(inp, outp,expkey);
        inp = inp+16;
        outp = outp + 16;
    }
        t1 = rdtsc32();
        inp = in;
        outp = out;
    if (tMin > t1-t0 - overhead) tMin = t1-t0 - overhead;
  }
  inp = in;
  outp = out;
  printf("Cycles for AES encryption: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/(16.0*BLOCKS*256));
    tMin = 0xFFFFFFFF

     for (j=0;j<1000;j++) {
            AES_decrypt( out,outd,expkeyd);
     }
     
      for (k=0;k < TIMER_SAMPLE_CNT;k++) {
                t0 = rdtsc32();
                for(i=0;i<256;i= i + 16){
                    AES_decrypt(inp, outp,expkeyd);
                    inp = inp+16;
                    outp = outp + 16;
                    }
                    t1 = rdtsc32();
                    inp = in;
                    outp = out;
                if (tMin > t1-t0 - overhead) tMin = t1-t0 - overhead;
  }
    
      printf("Cycles for AES decryption: %d\n", tMin);
  printf("Cycles per byte: %f\n", tMin/(16.0*BLOCKS*256));
  return 0;
}

