#include <string.h>
#include "print.h"
#include <stdio.h>
#include "wmmintrin.h" 
#include "smmintrin.h"

const unsigned char key[16] = {0x7f,0x7e,0x7d,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x70};
unsigned char plain[16] ={0xd4,0x57 ,0xf8,0xd1 ,0xb8,0xcc,0x74,0x6f ,0xa8,0x1b ,0xf6,0x60 ,0xb4,0x6f ,0x1d,0x86} ;// {0x74,0x68,0x69,0x73,0x20,0x69,0x73,0x20,0x73,0x6f,0x6d,0x65,0x20,0x70,0x6c,0x61};
__m128i roundkeys[11];
__m128i roundkeys_dec[11];
inline __m128i AES_128_ASSIST (__m128i temp1, __m128i temp2);
inline void AES_128_Key_Expansion (__m128i* Key_Schedule);
inline __m128i AES_ECB_encrypt(const __m128i in,const __m128i *key);
inline __m128i AES_ECB_decrypt(const __m128i in,const __m128i *key);

int main(){
int i;
  __m128i Cipher, Plain, Decrypt;
  roundkeys[0] = _mm_load_si128((__m128i*) key);
  Plain = _mm_load_si128((__m128i*) plain);
  AES_128_Key_Expansion(roundkeys);
  Cipher= AES_ECB_encrypt(Plain, roundkeys);
  AES_Key_Dec(roundkeys, roundkeys_dec);
	for(i=0;i<11;i++){
	  printvector(roundkeys[i],"roundkeys");
	  printvector(roundkeys_dec[i],"roundkeys_dec");}
  Decrypt= AES_ECB_decrypt(Plain, roundkeys_dec);
  printvector(roundkeys[0],"key");
  printvector(Plain,"plain");
  printvector(Cipher,"Cipher");
  printvector(Decrypt,"decrypt");
  return 0; 
}

/*AES*/
//key expansion
inline void AES_Key_Dec(const __m128i* enc_key, __m128i* dec_key)
{
	dec_key[10] = enc_key[0];
	dec_key[9] = _mm_aesimc_si128(enc_key[1]);
	dec_key[8] = _mm_aesimc_si128(enc_key[2]);
	dec_key[7] = _mm_aesimc_si128(enc_key[3]);
	dec_key[6] = _mm_aesimc_si128(enc_key[4]);
	dec_key[5] = _mm_aesimc_si128(enc_key[5]);
	dec_key[4] = _mm_aesimc_si128(enc_key[6]);
	dec_key[3] = _mm_aesimc_si128(enc_key[7]);
	dec_key[2] = _mm_aesimc_si128(enc_key[8]);
	dec_key[1] = _mm_aesimc_si128(enc_key[9]);
	dec_key[0] = enc_key[10];
}

inline __m128i AES_128_ASSIST (__m128i temp1, __m128i temp2)
{
__m128i temp3;
temp2 = _mm_shuffle_epi32 (temp2 ,0xff);
temp3 = _mm_slli_si128 (temp1, 0x4);
temp1 = _mm_xor_si128 (temp1, temp3);
temp3 = _mm_slli_si128 (temp3, 0x4);
temp1 = _mm_xor_si128 (temp1, temp3);
temp3 = _mm_slli_si128 (temp3, 0x4);
temp1 = _mm_xor_si128 (temp1, temp3);
temp1 = _mm_xor_si128 (temp1, temp2);
return temp1;
}
inline void AES_128_Key_Expansion (__m128i* Key_Schedule)
{
__m128i temp2;
temp2 = _mm_aeskeygenassist_si128(Key_Schedule[0] ,0x1);
Key_Schedule[1] = AES_128_ASSIST(Key_Schedule[0], temp2);
temp2 = _mm_aeskeygenassist_si128(Key_Schedule[1],0x2);
Key_Schedule[2] = AES_128_ASSIST(Key_Schedule[1], temp2);
temp2 = _mm_aeskeygenassist_si128(Key_Schedule[2],0x4);
Key_Schedule[3] = AES_128_ASSIST(Key_Schedule[2], temp2);
temp2 = _mm_aeskeygenassist_si128(Key_Schedule[3],0x8);
Key_Schedule[4] = AES_128_ASSIST(Key_Schedule[3], temp2);
temp2 = _mm_aeskeygenassist_si128(Key_Schedule[4],0x10);
Key_Schedule[5] = AES_128_ASSIST(Key_Schedule[4], temp2);
temp2 = _mm_aeskeygenassist_si128(Key_Schedule[5],0x20);
Key_Schedule[6] = AES_128_ASSIST(Key_Schedule[5], temp2);
temp2 = _mm_aeskeygenassist_si128(Key_Schedule[6],0x40);
Key_Schedule[7] = AES_128_ASSIST(Key_Schedule[6], temp2);
temp2 = _mm_aeskeygenassist_si128(Key_Schedule[7],0x80);
Key_Schedule[8] = AES_128_ASSIST(Key_Schedule[7], temp2);
temp2 = _mm_aeskeygenassist_si128(Key_Schedule[8],0x1b);
Key_Schedule[9] = AES_128_ASSIST(Key_Schedule[8], temp2);
temp2 = _mm_aeskeygenassist_si128(Key_Schedule[9],0x36);
Key_Schedule[10] = AES_128_ASSIST(Key_Schedule[9], temp2);

}

inline __m128i AES_ECB_decrypt(const __m128i in,// PLAINTEXT
const __m128i *key)
{
  __m128i tmp;
    tmp = _mm_xor_si128 (in,key[0]);
    tmp = _mm_aesdec_si128 (tmp,key[1]);
    tmp = _mm_aesdec_si128 (tmp,key[2]);
    tmp = _mm_aesdec_si128 (tmp,key[3]);
    tmp = _mm_aesdec_si128 (tmp,key[4]);
    tmp = _mm_aesdec_si128 (tmp,key[5]);
    tmp = _mm_aesdec_si128 (tmp,key[6]);
    tmp = _mm_aesdec_si128 (tmp,key[7]);
    tmp = _mm_aesdec_si128 (tmp,key[8]);
    tmp = _mm_aesdec_si128 (tmp,key[9]);
    tmp = _mm_aesdeclast_si128 (tmp,key[10]);
    return tmp;
}

inline __m128i AES_ECB_encrypt(const __m128i in,const __m128i *key)
{
  __m128i tmp;
    tmp = _mm_xor_si128 (in,key[0]);
    tmp = _mm_aesenc_si128 (tmp,key[1]);
    tmp = _mm_aesenc_si128 (tmp,key[2]);
    tmp = _mm_aesenc_si128 (tmp,key[3]);
    tmp = _mm_aesenc_si128 (tmp,key[4]);
    tmp = _mm_aesenc_si128 (tmp,key[5]);
    tmp = _mm_aesenc_si128 (tmp,key[6]);
    tmp = _mm_aesenc_si128 (tmp,key[7]);
    tmp = _mm_aesenc_si128 (tmp,key[8]);
    tmp = _mm_aesenc_si128 (tmp,key[9]);
    tmp = _mm_aesenclast_si128 (tmp,key[10]);
    return tmp;
}
