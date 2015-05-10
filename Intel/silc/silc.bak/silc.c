#include "wmmintrin.h"
#include "smmintrin.h"
#include <emmintrin.h>
#include <stdio.h>
#include <stdint.h>
#include "print.h"
#include <string.h>

inline __m128i AES_ECB_encrypt(const __m128i in,const __m128i *key);
inline void AES_128_Key_Expansion (__m128i* Key_Schedule);
inline __m128i Hash(unsigned char* A,  unsigned long long alen, __m128i* roundkeys, unsigned char* N, int nlen );
inline __m128i g(__m128i in);
inline __m128i PRF(__m128i V, __m128i* C, unsigned long long mlen, __m128i* roundkeys);
inline __m128i zpp(__m128i* M, int mlen);
inline __m128i zap(__m128i* M, int mlen);


void SILC_AES128_ENC(const unsigned char* K,unsigned char* M,  unsigned long long mlen, unsigned char* C, unsigned char* N,  int nlen, unsigned char* A,  unsigned long long alen, unsigned char* T){
	__m128i V,state, temp, msb;
	__m128i* Mpointer = (__m128i*) M;
	__m128i* Cpointer = (__m128i*) C;
	msb = _mm_setr_epi8(0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
	__m128i roundkeys[11];
	unsigned long long i, max;
	roundkeys[0] = _mm_load_si128((__m128i*) K);
	AES_128_Key_Expansion(roundkeys);
	V = Hash( A, alen, roundkeys, N, nlen);
	state = AES_ECB_encrypt(V,roundkeys);
	printvector(state,"Venc");
	max = (mlen+15)>>4;
	for(i = 0; i<max-1; i++){
	Cpointer[i] = _mm_xor_si128(state, Mpointer[i]);
	temp = _mm_or_si128(msb, Cpointer[i]);
	printvector(temp,"after Fix1");
	state = AES_ECB_encrypt(temp,roundkeys);
	printvector(state,"state after enc");
	printf("ia:%lli\n",i);
	}
	printvector(state,"state after loop");
	Cpointer[max-1] = _mm_xor_si128(state, Mpointer[max-1]);
	printvector(Cpointer[max-1],"After xoring last partial message block:");
	temp  = PRF(V, Cpointer, mlen, roundkeys);
	_mm_store_si128((__m128i*) T, temp);

}

int SILC_AES128_DEC(const unsigned char* K,unsigned char* M,  unsigned long long mlen, unsigned char* C, unsigned char* N,  int nlen, unsigned char* A,  unsigned long long alen, unsigned char* T){
	__m128i V,state, temp, msb , Tagorg;
	__m128i* Mpointer = (__m128i*) M;
	__m128i* Cpointer = (__m128i*) C;
	__m128i roundkeys[11];
	unsigned long long i, max;
	roundkeys[0] = _mm_load_si128((__m128i*) K);
	AES_128_Key_Expansion(roundkeys);
	Tagorg = _mm_load_si128((__m128i*) T);
	V = Hash(A, alen, roundkeys, N, nlen);

	temp = PRF(V, Cpointer, mlen, roundkeys);
	if(!_mm_test_all_ones(_mm_cmpeq_epi8(temp,Tagorg))){ //1 if same, -1 if different
		return -1;
	}
	msb = _mm_setr_epi8(0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);

	state = AES_ECB_encrypt(V,roundkeys);
	max = (mlen+15)>>4;
	for(i = 0; i<max-1; i++){
	Mpointer[i] = _mm_xor_si128(state, Cpointer[i]);
	temp = _mm_or_si128(msb, Cpointer[i]);
	state = AES_ECB_encrypt(temp,roundkeys);
	
	}
	temp = _mm_xor_si128(state, Cpointer[max-1]);
	_mm_store_si128(Mpointer +max-1, temp); 

	PRF(V, Cpointer, mlen, roundkeys);
	return 1;
}

inline __m128i Hash(unsigned char* A,  unsigned long long alen, __m128i* roundkeys, unsigned char* N, int nlen ){
	__m128i V, state, temp;
	int i, max;
	__m128i* Apointer = (__m128i*) A;
	temp = zpp((__m128i*)N, 16-nlen );
	printvector(temp,"state");
	state = AES_ECB_encrypt(temp, roundkeys);
	printvector(state,"stateaftenc");
	if(alen == 0){
	  V = g(state);
	  return V;
	}
	max = alen>>4;
	for(i = 0; i<max; i++){
	 	temp = _mm_xor_si128(Apointer[i], state);
		printvector(temp,"statexor");
		state = AES_ECB_encrypt(temp, roundkeys);
	}
			printvector(state,"statexorenc");

	if(alen%16){
	temp = zap((__m128i*)A + max,(int) alen%16);
	state = _mm_xor_si128(temp, state);
	state = AES_ECB_encrypt(state, roundkeys);
	}
	unsigned long long t_alen = alen;
	for(i = 0; i < sizeof(unsigned long long); i++) {
	  	temp = _mm_set_epi8((char) t_alen,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
		state = _mm_xor_si128(temp, state);
		t_alen = t_alen>>8;
	}
	printvector(state,"statexorenclen");

	V = g(state);
	printvector(V,"after g");
	return V;
}

inline __m128i PRF(__m128i V, __m128i* C, unsigned long long mlen, __m128i* roundkeys){
	__m128i state, tag, temp; 
	unsigned long long  i, max;
	state = g(V);
	printvector(state,"state after g");
	state = AES_ECB_encrypt(state,roundkeys);
	printvector(state,"state after g enc");

	if(mlen == 0){
		temp = g(state);
		tag = AES_ECB_encrypt(temp,roundkeys);
	    return tag;
	}
	max = mlen>>4;
	for(i = 0; i<max; i++){
		printf("i:%lli\n",i);
		temp = _mm_xor_si128(C[i], state);
		printvector(temp, "tag state");
		state = AES_ECB_encrypt(temp,roundkeys);
		printvector(state, "tag state after enc");
	}
	if(mlen%16){	  
		temp = zap(C+max, mlen%16);
		printvector(temp, "Czap");
		temp = _mm_xor_si128(temp, state);
		printvector(temp, "TS before enc");
		state = AES_ECB_encrypt(temp,roundkeys);
		printvector(state,"partial blok processed TS");

	}
	unsigned long long t_mlen = mlen;
	for(i = 0; i < sizeof(unsigned long long); i++) {
		temp = _mm_set_epi8((char) t_mlen,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
		state = _mm_xor_si128(temp, state);
		t_mlen = t_mlen>>8;
	}
	printvector(state, "tag state after xoring");

	temp = g(state);
	tag = AES_ECB_encrypt(temp,roundkeys);
	printvector(tag, "tag");
	return tag;
}

//prepending and appending functions

inline __m128i zpp(__m128i* M, int mlen){
	__m128i result = _mm_load_si128( M);
	switch(mlen){
	  case 1:
	    result = _mm_slli_si128(result,1);
	    break;
	  case 2:
	    	result = _mm_slli_si128(result,2);
	    break;
	  case 3:
	    	result = _mm_slli_si128(result,3);
	    break;
	  case 4:
	    	result = _mm_slli_si128(result,4);
	    break;
	  case 5:
	    	result = _mm_slli_si128(result,5);
	    break;
	  case 6:
	    	result = _mm_slli_si128(result,6);
	    break;
	  case 7:
	    	result = _mm_slli_si128(result,7);
	    break;
	  case 8:
	   	result = _mm_slli_si128(result,8);
	    break;
	  case 9:
	    	result = _mm_slli_si128(result,9);
	    break;
	  case 10:
	    	result = _mm_slli_si128(result,10);
	    break;
	  case 11:
	    	result = _mm_slli_si128(result,11);
	    break;
	  case 12:
	    	result = _mm_slli_si128(result,12);
	    break;
	  case 13:
	    	result = _mm_slli_si128(result,13);
	    break;
	  case 14:
	    	result = _mm_slli_si128(result,14);
	    break;
	  case 15:
	    	result = _mm_slli_si128(result,15);
	    break;
	}
	return result;
}

inline __m128i zap(__m128i* M, int mlen){
	__m128i result = _mm_load_si128(M);
	switch(mlen){
	  case 1:
	    result = _mm_slli_si128(result,15);
	    result = _mm_srli_si128(result,15);
	    break;
	  case 2:
	    	result = _mm_slli_si128(result,14);
		result = _mm_srli_si128(result,14);
	    break;
	  case 3:
	    	result = _mm_slli_si128(result,13);
	    	result = _mm_srli_si128(result,13);
	    break;
	  case 4:
	    	result = _mm_slli_si128(result,12);
	    	result = _mm_srli_si128(result,12);
	    break;
	  case 5:
	    	result = _mm_slli_si128(result,11);
	    	result = _mm_srli_si128(result,11);
	    break;
	  case 6:
	    	result = _mm_slli_si128(result,10);
	    	result = _mm_srli_si128(result,10);
	    break;
	  case 7:
	    	result = _mm_slli_si128(result,9);
	    	result = _mm_srli_si128(result,9);
	    break;
	  case 8:
	   	result = _mm_slli_si128(result,8);
	   	result = _mm_srli_si128(result,8);
	    break;
	  case 9:
	    	result = _mm_slli_si128(result,7);
	    	result = _mm_srli_si128(result,7);
	    break;
	  case 10:
// 		printvector(result,"result1");
	    	result = _mm_slli_si128(result,6);
// 		printvector(result,"result2");
	    	result = _mm_srli_si128(result,6);
// 		printvector(result,"result3");
	    break;
	  case 11:
	    	result = _mm_slli_si128(result,5);
	    	result = _mm_srli_si128(result,5);
	    break;
	  case 12:
	    	result = _mm_slli_si128(result,4);
	    	result = _mm_srli_si128(result,4);
	    break;
	  case 13:
	    	result = _mm_slli_si128(result,3);
	    	result = _mm_srli_si128(result,3);
	    break;
	  case 14:
	    	result = _mm_slli_si128(result,2);
	    	result = _mm_srli_si128(result,2);
	    break;
	  case 15:
	    	result = _mm_slli_si128(result,1);
	    	result = _mm_srli_si128(result,1);
	    break;
	}
	return result;
}

inline __m128i g(__m128i in){
	__m128i result, temp1, temp2;
	__m128i mask =_mm_setr_epi16(0x0201,0x0403,0x0605,0x0807,0x0a09,0x0c0b,0x0e0d,0x000f);
	temp1 = _mm_shuffle_epi8(in, mask);
	temp2 = _mm_slli_si128(temp1,15);
	result = _mm_xor_si128(temp2,temp1);
	return result;
}

/*AES*/
//key expansion


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



