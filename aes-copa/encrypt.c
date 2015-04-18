/*
 * AES-COPA v1 reference implementation
 *
 * copa@esat.kuleuven.be
 */

#include "crypto_aead.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aes-core.h"
#include "print.h"


typedef uint8_t block_t[16];

/* 
 * Debugging support 
 */
#define PRINT(b)	printblock(#b, b)
#define PRINT1(b)	if (i == 3*16) printblock(#b, b)
#define PRINTI(i)	printf("%s: %d\n", #i, i)
// static void printblock(const char* caption, const block_t buf)
// {
// 	int i;
// 
// 	printf("%-17s: ", caption);
// 	for (i = 0; i < 16; i++) {
// 		printf("%02x", buf[i]);
// 	}
// 	putchar('\n');
// }

/* 
 * Auxiliary routines: operations on 128-bit blocks, multiplications, AES
 */
#define copy_block(d, s) memcpy(d, s, 16)
#define GETU32(p) (((uint32_t)(p)[3]) ^ ((uint32_t)(p)[2] << 8) ^ ((uint32_t)(p)[1] << 16) ^ ((uint32_t)(p)[0] << 24))//3 sh + 3 xor
#define PUTU32(c, s) { (c)[3] = (uint8_t)(s); (c)[2] = (uint8_t)((s)>>8); (c)[1] = (uint8_t)((s)>>16); (c)[0] = (uint8_t)((s)>>24); } //3 sh


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
	block_t x2, x4;
	uint32_t* xp =(uint32_t*) x;
	uint32_t* x2p =(uint32_t*) x2,
	uint32_t* x4p =(uint32_t*) x4;
	uint32_t* resp =(uint32_t*) res;
	int msb = x[0] & 0x80;
	shl_block(x2, x);
	if (msb) {
		x2[15] ^= 0x87;
	}
	msb = x2[0] & 0x80;
	shl_block(x4, x2);
	if (msb) {
		x4[15] ^= 0x87;
	}
// 	xor_block(x4, x4, x2);
// 	xor_block(res, x4, x);
	resp[0] = xp4[0]^xp2[0]^xp[0];
	resp[1] = xp4[1]^xp2[1]^xp[1];
	resp[2] = xp4[2]^xp2[2]^xp[2];
	resp[3] = xp4[3]^xp2[3]^xp[3];
}

/*
 * COPA's AD processing PMAC1'
 */

void inline mac(unsigned char* out, 
		const unsigned char* in, unsigned long long len, 
		const unsigned char* LL,
		 unsigned char* expkey)
{
	block_t v = { 0 }, delta, block;
	unsigned int i;

	gf128_mul3(delta, LL);
	gf128_mul3(delta, delta);
	gf128_mul3(delta, delta); /* delta = 3^3*L */
	/* mac full blocks except last */
	while (len > 16) {
		xor_block(block, in, delta);
		aesc_encrypt(block, block, expkey);
		xor_block(v, v, block);
		gf128_mul2(delta, delta);

		in += 16;
		len -= 16;
	}
	if (len == 16) { /* last block full */
		gf128_mul3(delta, delta);
		xor_block(v, v, delta);
		xor_block(v, v, in);
		aesc_encrypt( v,out, expkey);
	} else { /* last block partial */
		gf128_mul3(delta, delta);
		gf128_mul3(delta, delta);
		xor_block(v, v, delta);
		for (i = 0; i < len; i++) {
			v[i] ^= in[i];
		}
		v[len] ^= 0x80; /* padding */
		aesc_encrypt(v,out, expkey);
	}
}

/*
 * Encryption and decryption with tag splitting (for messages smaller than one
 * block).
 */

static inline void encrypt_tag_splitting(unsigned char* c, 
		const unsigned char* m, int mlen, 
		const block_t V, const block_t LL,  unsigned char* expkey)
{
	block_t delta36, delta37, delta38, delta236, delta367;
	block_t padmsg = { 0 }, block, S, C, T;
	int i;

	copy_block(delta36, LL);
	for (i = 0; i < 6; i++) {
		gf128_mul3(delta36, delta36);
	}
	gf128_mul3(delta37, delta36);
	gf128_mul3(delta38, delta37);
	gf128_mul2(delta236, delta36);
	gf128_mul7(delta367, delta36);
	for (i = 0; i < mlen; i++) {
		padmsg[i] = m[i];
	}
	padmsg[mlen] = 0x80; /* padding */

	/* encrypt */
	xor_block(block, padmsg, delta37);
	aesc_encrypt(block, block, expkey);
	xor_block(block, block, delta36);
	xor_block(S, block, V);

	aesc_encrypt(S,block, expkey);
	xor_block(C, block, delta236);

	/* tag */
	xor_block(block, padmsg, delta38);
	aesc_encrypt(block, block, expkey);
	xor_block(block, block, S);
	aesc_encrypt(block, block, expkey);
	xor_block(T, block, delta367);

	/* fill c[0..mlen-1+16] with bytes from C and T */
	for (i = 0; i < 16; i++) {
		c[i] = C[i];
	}
	for (i = 16; i < mlen+16; i++) {
		c[i] = T[i-16];
	}
}

static inline int decrypt_tag_splitting(unsigned char* m, int mlen, 
		const unsigned char* c, 
		const block_t V, const block_t LL, unsigned char* expkey)
{
	block_t delta36, delta37, delta38, delta236, delta367;
	block_t block, S, M, T;
	const unsigned char *p = &M[15];
	int i;

	copy_block(delta36, LL);
	for (i = 0; i < 6; i++) {
		gf128_mul3(delta36, delta36);
	}
	gf128_mul3(delta37, delta36);
	gf128_mul3(delta38, delta37);
	gf128_mul2(delta236, delta36);
	gf128_mul7(delta367, delta36);

	copy_block(block, c); /* copies from partial ciphertext + partial tag */
	xor_block(block, block, delta236);
	aesc_decrypt( block, S,expkey);

	xor_block(block, V, S);
	xor_block(block, block, delta36);
	aesc_decrypt(block, block, expkey);

	xor_block(M, block, delta37); /* block = M10*   */
	/* compute tag */
	xor_block(block, M, delta38);
	aesc_encrypt(block, block, expkey);
	xor_block(block, block, S);
	aesc_encrypt(block, block, expkey);
	xor_block(T, block, delta367);

	while (*p == 0)
		p--;
	if ((*p != 0x80) || (p-M != mlen)) {
		return -1;
	}

	if (memcmp(c+16, T, mlen) == 0) {
		for (i = 0; i < mlen; i++) {
			m[i] = M[i];
		}
		return 0;
	} else {
		return -1;
	}
}

/*
 * XLS + auxiliary routines for handling fractional last blocks
 */

void inline rol(unsigned char* out, const unsigned char* in, unsigned int s)
{
	unsigned char firstbit = in[0] >> 7;
	while (--s > 0) {
		unsigned char bit = in[1] >> 7;

		*out++ = (*in++ << 1) | bit;
	}

	*out = (*in << 1) | firstbit;
}

void inline mix(unsigned char* buf, unsigned int s)
{
	unsigned char ab[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	unsigned int i;

	for (i = 0; i < s; i++) {
		ab[i] = buf[i] ^ buf[s+i]; //A xor B
	}
	rol(ab, ab, s);

	for (i = 0; i < s; i++) {
		buf[i] ^= ab[i];
		buf[s+i] ^= ab[i];
	}
}

void inline xls(unsigned char* buf, unsigned int s, const block_t twod1,  unsigned char* expkey)
{
	/*
	 * Input is s+16 bytes buf[0]..buf[s+15] with 1 < s < 16
	 */                     

	block_t LL, LL3;
	gf128_mul7(LL, twod1); 
	gf128_mul7(LL, LL); /* LL = 2^(d-1) * 7^2 * L  */
	gf128_mul3(LL3, LL); /* LL3 = 2^(d-1) * 3 * 7^2 * L  */

	/* Ed,2 on first 16 bytes */
	xor_block(buf, buf, LL3);
	aesc_encrypt(buf, buf, expkey);
	xor_block(buf, buf, LL3);

	/* mix on last 2s bytes */
	mix(buf+16-s, s);
	/* flip */
	buf[16-s] ^= 0x80;

	/* Ed,1 on first 16 bytes */
	xor_block(buf, buf, LL);
	aesc_encrypt(buf, buf, expkey);
	xor_block(buf, buf, LL);

	/* flip */
	buf[16-s] ^= 0x80;
	/* mix on last 2s bytes */
	mix(buf+16-s, s);

	/* Ed,2 on first 16 bytes */
	xor_block(buf, buf, LL3);
	aesc_encrypt(buf, buf, expkey);
	xor_block(buf, buf, LL3);
}

void inline xlsinv(unsigned char* buf, unsigned int s, const block_t twod1,  unsigned char* expkey)
{
	block_t LL, LL3;
	gf128_mul7(LL, twod1); 
	gf128_mul7(LL, LL); /* LL = 2^(d-1) * 7^2 * L  */
	gf128_mul3(LL3, LL); /* LL3 = 2^(d-1) * 3 * 7^2 * L  */

	/* Ed,2 on first 16 bytes */
	xor_block(buf, buf, LL3);
	aesc_decrypt(buf, buf, expkey);
	xor_block(buf, buf, LL3);

	/* mix on last 2s bytes */
	mix(buf+16-s, s);
	/* flip  */
	buf[16-s] ^= 0x80;

	/* Ed,1 on first 16 bytes */
	xor_block(buf, buf, LL);
	aesc_decrypt(buf, buf, expkey);
	xor_block(buf, buf, LL);

	/* flip */
	buf[16-s] ^= 0x80;
	/* mix on last 2s bytes */
	mix(buf+16-s, s);

	/* Ed,2 on first 16 bytes */
	xor_block(buf, buf, LL3);
	aesc_decrypt(buf, buf, expkey);
	xor_block(buf, buf, LL3);
}

/*
 * main encryption and decryption routines
 */

int crypto_aead_encrypt(
       unsigned char *c,unsigned long long *clen,
       const unsigned char *m,unsigned long long mlen,
       const unsigned char *ad,unsigned long long adlen,
       const unsigned char *nsec,
       const unsigned char *npub,
       const unsigned char *k
     )
{
  
	unsigned char* macdata;
	const unsigned char* in = m;
	unsigned char* out = c;
	unsigned long long remaining = mlen;
	unsigned char expkey[11*16];

	aesc_keyexp(k, expkey);
	block_t V;
	block_t lastblock;
	block_t block, Lup, Ldown, twod1;
	block_t checksum = { 0 };
	block_t T;
	block_t LL = { 0 };

	//AES_ENCRYPT(LL, LL, expkey); /* LL = AES(LL) */
	aesc_encrypt(LL, LL, expkey);

	*clen = mlen + 16;

	/* mac AD + nonce */
	macdata = malloc(adlen + 16);
	memcpy(macdata, ad, adlen);
	memcpy(macdata+adlen, npub, 16);
	mac(V, macdata, adlen+16, LL, expkey);
	free(macdata);
	if (mlen < 16) {
		encrypt_tag_splitting(c, m, mlen, V, LL, expkey);
		return 0;
	}

	xor_block(lastblock, LL, V); /* lastblock = LL xor V */
	copy_block(twod1, LL); /* 2^(d-1)*L where d is # of blocks. */
	gf128_mul3(Lup, LL); /* Lup = 3*LL delta0*/ 
	gf128_mul2(Ldown, LL); /* Ldown = 2*LL  delta1*/
	
	while (remaining >= 16) { 
		xor_block(checksum, checksum, in);//calc sigma
		
		xor_block(block, in, Lup);//mi xor delta0
		//AES_ENCRYPT(block, block, expkey);//E_k(mi xor delta0)
		aesc_encrypt(block, block, expkey);
		xor_block(block, block, lastblock);//E_k(mi xor delta0) XOR V[i-1]
		copy_block(lastblock, block);//V[i] = E_k(mi xor delta0) XOR V[i-1]
		aesc_encrypt(block, block, expkey);//E_k(v[i]
		xor_block(out, block, Ldown);//E_k(v[i]) xor delta1
		gf128_mul2(Lup, Lup);//delta0*2
		gf128_mul2(Ldown, Ldown);//delta1*2
		if (remaining < mlen) {
			gf128_mul2(twod1, twod1);//calc  2^(d-1)*L
		}
		
		in += 16;
		out += 16;
		remaining -= 16;
	}
	/* compute tag */
	gf128_mul3(LL, twod1);//2^(d-1)3L
	gf128_mul3(LL, LL);//2^(d-1)3^2L
	xor_block(checksum, checksum, LL);//sigma XOR 2^(d-1)3^2L
	aesc_encrypt(checksum, checksum, expkey);//E_K(sigma XOR 2^(d-1)3^2L)

	xor_block(checksum, checksum, lastblock);//E_K(sigma XOR 2^(d-1)3^2L) XOR S

	aesc_encrypt(checksum, checksum, expkey);//E_K(E_K(sigma XOR 2^(d-1)3^2L) XOR S)
	gf128_mul7(LL, twod1);//2^(d-1)7L
	xor_block(T, checksum, LL);//E_K(E_K(sigma XOR 2^(d-1)3^2L) XOR S) XOR 2^(d-1)7L
	if (remaining == 0) { /* last block full, we are done */
		copy_block(out, T);

	} else { /* last partial block remaining, use XLS */
		unsigned char buf[32]; /* at most 15 + 16 bytes */

		memcpy(buf, in, remaining);
		memcpy(buf+remaining, T, 16);
		xls(buf, remaining, twod1, expkey);

		memcpy(out, buf, remaining+16); /* last partial ciphertext + tag */
	}
      
	return 0;
}



int crypto_aead_decrypt(
   unsigned char *m,unsigned long long *mlen,
   unsigned char *nsec,
   const unsigned char *c,unsigned long long clen,
   const unsigned char *ad,unsigned long long adlen,
   const unsigned char *npub,
   const unsigned char *k
   )
{
	unsigned char* macdata;
	const unsigned char* in = c;
	unsigned char* out = m;
	unsigned long long remaining;

	const unsigned char* T;
	unsigned char buf[32]; /* for XLS: at most 15 + 16 bytes */
		unsigned char expkey[11*16];

	aesc_keyexp(k, expkey);
	block_t V;
	block_t lastblock;
	block_t checksum = { 0 };
	block_t tag;
	block_t block, Lup, Ldown, twod1;
	block_t LL = { 0 };

	aesc_encrypt(LL, LL, expkey); /* LL = AES(LL) */

	//*mlen = clen;copy_block

	/* mac AD + nonce */
	macdata = malloc(adlen + 16);
	memcpy(macdata, ad, adlen);
	memcpy(macdata+adlen, npub, 16);
	mac(V, macdata, adlen+16, LL, expkey);
	free(macdata);
	if (clen < 16) {
		return decrypt_tag_splitting(m, clen, c, V, LL, expkey);
	}

	xor_block(lastblock, LL, V); /* lastblock = LL ^ V; */

	copy_block(twod1, LL); /* 2^(d-1)*L where d is # of blocks. */
	gf128_mul3(Lup, LL); /* Lup = 3*LL */
	gf128_mul2(Ldown, LL); /* Ldown = 2*LL */
	remaining = clen;
	while (remaining >= 16) {
		block_t newlastblock;
		xor_block(block, in, Ldown);

		aesc_decrypt( block,newlastblock, expkey);
		xor_block(block, newlastblock, lastblock);
		copy_block(lastblock, newlastblock);

		aesc_decrypt(block, block, expkey);
		xor_block(out, block, Lup);
		xor_block(checksum, checksum, out);

		gf128_mul2(Lup, Lup);
		gf128_mul2(Ldown, Ldown);
		if (remaining < clen) {
			gf128_mul2(twod1, twod1);
		}

		in += 16;
		out += 16;
		remaining -= 16;
	}
	
	if (remaining == 0) { /* last block full, take tag from input */
		T = in;
	} else { /* last partial block remaining, use XLS^-1 */
;
		memcpy(buf, in, remaining+16);
		in += remaining;
		xlsinv(buf, remaining, twod1, expkey);

		memcpy(out, buf, remaining); /* last partial plaintext */
		T = buf + remaining;
	}

	/* compute tag */
	gf128_mul3(LL, twod1);
	gf128_mul3(LL, LL);//2^(d-1)3^2L
	xor_block(checksum, checksum, LL);//sigma XOR 2^(d-1)3^2L
	aesc_encrypt(checksum, checksum, expkey);//E_K(sigma XOR 2^(d-1)3^2L)

	xor_block(checksum, checksum, lastblock);//E_K(sigma XOR 2^(d-1)3^2L) XOR S

	aesc_encrypt(checksum, checksum, expkey);//E_K(E_K(sigma XOR 2^(d-1)3^2L) XOR S)
	gf128_mul7(LL, twod1);//2^(d-1)7L
	xor_block(tag, checksum, LL);//E_K(E_K(sigma XOR 2^(d-1)3^2L) XOR S) XOR 2^(d-1)7L

	if (memcmp(tag, T, 16) == 0) {
		return 0;
	} else {
		return -1;
	}
}

