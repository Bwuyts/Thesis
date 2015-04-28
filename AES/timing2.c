#include <stdio.h>
#include <string.h> /* memcpy() */
#include <stdint.h> /* uint32_t */
#include <stdlib.h>
#include <time.h>
#include "enable_arm_pmu2/armpmu_lib.h"


#include "aes.h"

#define BLOCKS 1
typedef uint8_t block_t[16];
 #define TIMER_SAMPLE_CNT (10000)
static inline void gf128_mul2(block_t res, const block_t x)
{
	int msb = x[0] & 0x80;
	shl_block(res, x);
	if (msb) {
		res[15] ^= 0x87;
	}
}

static inline void gf128_mul3(block_t res, const block_t x)
{
	block_t x2;
	int msb = x[0] & 0x80;
	shl_block(x2, x);
	if (msb) {
		x2[15] ^= 0x87;
	}
	xor_block(res, x2, x);
}

static inline void gf128_mul7(block_t res, const block_t x)
{
//	block_t x2, x4;
	uint32_t X0, X1,X2,X3;
	uint32_t X0_2, X1_2,X2_2,X3_2;
	uint32_t X0_4, X1_4,X2_4,X3_4;
	uint32_t res0,res1,res2,res3;
// 	uint32_t* xp =(uint32_t*) x;
// 	uint32_t* x2p =(uint32_t*) x2;
// 	uint32_t* x4p =(uint32_t*) x4;
// 	uint32_t* resp =(uint32_t*) res;
	int msb = x[0] & 0x80;
	X0 = GETU32(x);
	X1 = GETU32(x+4);
	X2 = GETU32(x+8);
	X3 = GETU32(x+12);
	X0_2 = (X0<<1) | (X1>>31);
	X1_2 = (X1<<1) | (X2>>31);
	X2_2 = (X2<<1) | (X3>>31);
	X3_2 = (X3<<1) ;
	if (msb) {
		X3_2 ^= 0x87;
	}
	
	msb = X0_2 & 0x80000000;
//	shl_block(x4, x2);
	X0_4 = (X0_2<<1) | (X1_2>>31);
	X1_4 = (X1_2<<1) | (X2_2>>31);
	X2_4 = (X2_2<<1) | (X3_2>>31);
	X3_4 = (X3_2<<1) ;
	if (msb) {
		X3_4^= 0x87;
	}
	res0 = X0_4^X0_2^X0;
	res1 = X1_4^X1_2^X1;
	res2 = X2_4^X2_2^X2;
	res3 = X3_4^X3_2^X3;
	PUTU32(res, res0);
	PUTU32(res+4, res1);
	PUTU32(res+8, res2);
	PUTU32(res+12, res3);
}
int main() {

const unsigned char key[16] = {0x7f,0x7e,0x7d,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x70};
const unsigned char out[16];

//asm volatile ("mcr p15,  0, %0, c15,  c9, 0\n" : : "r" (1));
  int i, j, k, l=100;

//  srand(time(NULL));
  
   uint32_t overhead = rdtsc32();
   overhead = rdtsc32() - overhead; 
  
   printf("Cycles for calibrate: %d\n", overhead);

  
   uint32_t t0,t1;
        /* big number to start */
    uint32_t tMin = 0xFFFFFFFF;   
  
    tMin = 0xFFFFFFFF;

     for (j=0;j<1000;j++) {
            gf128_mul2(out, key);
     }
     
      for (k=0;k < TIMER_SAMPLE_CNT;k++) {
                t0 = rdtsc32();
            gf128_mul2(out, key);

                    t1 = rdtsc32();
                if (tMin > t1-t0 - overhead) tMin = t1-t0 - overhead;
  }
    
      printf("GF2: %d\n", tMin);
      printf("Cycles per byte: %f\n", tMin/(16));
          tMin = 0xFFFFFFFF;

     for (j=0;j<1000;j++) {
            gf128_mul3(out, key);
     }
     
      for (k=0;k < TIMER_SAMPLE_CNT;k++) {
                t0 = rdtsc32();
            gf128_mul3(out, key);

                    t1 = rdtsc32();
                if (tMin > t1-t0 - overhead) tMin = t1-t0 - overhead;
  }
    
      printf("GF3: %d\n", tMin);
      printf("Cycles per byte: %f\n", tMin/(16));
          tMin = 0xFFFFFFFF;

     for (j=0;j<1000;j++) {
            gf128_mul7(out, key);
     }
     
      for (k=0;k < TIMER_SAMPLE_CNT;k++) {
                t0 = rdtsc32();
            gf128_mul7(out, key);

                    t1 = rdtsc32();
                if (tMin > t1-t0 - overhead) tMin = t1-t0 - overhead;
  }
    
      printf("GF7: %d\n", tMin);
      printf("Cycles per byte: %f\n", tMin/(16));
  return 0;
}

