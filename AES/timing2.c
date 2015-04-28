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
#define copy_block(d, s) memcpy(d, s, 16)
#define GETU32(p) (((uint32_t)(p)[3]) ^ ((uint32_t)(p)[2] << 8) ^ ((uint32_t)(p)[1] << 16) ^ ((uint32_t)(p)[0] << 24))//3 sh + 3 xor
#define PUTU32(c, s) { (c)[3] = (uint8_t)(s); (c)[2] = (uint8_t)((s)>>8); (c)[1] = (uint8_t)((s)>>16); (c)[0] = (uint8_t)((s)>>24); }
static inline void xor_block(block_t dest, const block_t a, const block_t b)
{
	uint32_t* destp = (uint32_t*) dest;
	uint32_t* ap = (uint32_t*) a;
	uint32_t* bp = (uint32_t*) b;
		destp[0] = ap[0] ^ bp[0];
		destp[1] = ap[1] ^ bp[1];
		destp[2] = ap[2] ^ bp[2];
		destp[3] = ap[3] ^ bp[3];
// 		dest[4] = a[4] ^ b[4];
// 		dest[5] = a[5] ^ b[5];
// 		dest[6] = a[6] ^ b[6];
// 		dest[7] = a[7] ^ b[7];
// 		dest[8] = a[8] ^ b[8];
// 		dest[9] = a[9] ^ b[9];
// 		dest[10] = a[10] ^ b[10];
// 		dest[11] = a[11] ^ b[11];
// 		dest[12] = a[12] ^ b[12];
// 		dest[13] = a[13] ^ b[13];
// 		dest[14] = a[14] ^ b[14];
// 		dest[15] = a[15] ^ b[15];
}

// static inline void copy_block(block_t dest, const block_t src)
// {
// 		uint32_t* destp = (uint32_t*) dest;
// 		uint32_t* srcp = (uint32_t*) src;
// 		destp[0] = srcp[0];
// 		destp[1] = srcp[1];
// 		destp[2] = srcp[2];
// 		destp[3] = srcp[3];
// // 		dest[4] = src[4];
// // 		dest[5] = src[5];
// // 		dest[6] = src[6];
// // 		dest[7] = src[7];
// // 		dest[8] = src[8];
// // 		dest[9] = src[9];
// // 		dest[10] = src[10];
// // 		dest[11] = src[11];
// // 		dest[12] = src[12];
// // 		dest[13] = src[13];
// // 		dest[14] = src[14];
// // 		dest[15] = src[15];
// 		
// }

static inline void shl_block(block_t res, const block_t x)
{
  uint32_t x0, x1,x2,x3,res0,res1,res2,res3;//31 sh + 12 xor + 3 or
	x0 = GETU32(x);
	x1 = GETU32(x+4);
	x2 = GETU32(x+8);
	x3 = GETU32(x+12);
	res0 = (x0<<1) | (x1>>31);
	res1 = (x1<<1) | (x2>>31);
	res2 = (x2<<1) | (x3>>31);
	res3 = (x3<<1) ;
	PUTU32(res, res0);
	PUTU32(res+4, res1);
	PUTU32(res+8, res2);
	PUTU32(res+12, res3);
/*
	res[0] = (x[0] << 1) | (x[1] >> 7);
	res[1] = (x[1] << 1) | (x[2] >> 7);
	res[2] = (x[2] << 1) | (x[3] >> 7);
	res[3] = (x[3] << 1) | (x[4] >> 7);
	res[4] = (x[4] << 1) | (x[5] >> 7);
	res[5] = (x[5] << 1) | (x[6] >> 7);
	res[6] = (x[6] << 1) | (x[7] >> 7);
	res[7] = (x[7] << 1) | (x[8] >> 7);
	res[8] = (x[8] << 1) | (x[9] >> 7);
	res[9] = (x[9] << 1) | (x[10] >> 7);
	res[10] = (x[10] << 1) | (x[11] >> 7);
	res[11] = (x[11] << 1) | (x[12] >> 7);
	res[12] = (x[12] << 1) | (x[13] >> 7);
	res[13] = (x[13] << 1) | (x[14] >> 7);
	res[14] = (x[14] << 1) | (x[15] >> 7);

	res[15] = x[15] << 1;*/
}
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

 unsigned char key[16] = {0x7f,0x7e,0x7d,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x70};
unsigned char out[16];

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
                      printf("GF2: %d\n", t0);

                for(i=0;i<1000000000;i++)
                    gf128_mul2(out, key);
                t1 = rdtsc32();
                      printf("GF2: %d\n", t1);

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

