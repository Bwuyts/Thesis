#include "wmmintrin.h"
#include "smmintrin.h"
#include <stdio.h>
#include <stdint.h>
//#include "print.h"
#include <string.h>


__m128i gf128Mul2(__m128i in);
__m128i gf128Mul3(__m128i in);
__m128i gf128Mul7(__m128i in);
inline void AES_Key_Dec(__m128i* enc_key, __m128i* dec_key);
__m128i pmac(__m128i* in, int inlen, __m128i L, __m128i* roundkeys);
// inline __m128i encrypt(__m128i V, __m128i L, __m128i* M,__m128i* C, int mlen, __m128i* roundkeys );
// __m128i decrypt(__m128i V, __m128i L, __m128i* C,__m128i* M, int mlen, __m128i* roundkeys );
void AES_COPA_encrypt(unsigned char* M,int mlen, unsigned char* A, int Alen, unsigned char* N, int Nlen, unsigned char*C,  unsigned char* T , const unsigned char* K);
int AES_COPA_decrypt( unsigned char* C,int clen, unsigned char * A, int Alen, unsigned char* N, int Nlen,unsigned char*M,unsigned char* T , const unsigned char* K);
inline __m128i AES_128_ASSIST (__m128i temp1, __m128i temp2);
inline void AES_128_Key_Expansion (__m128i* Key_Schedule);
inline __m128i padd(__m128i P, int length);
inline __m128i AES_ECB_encrypt(const __m128i in,const __m128i *key);
inline __m128i AES_ECB_decrypt(const __m128i in,const __m128i *key);
__m128i encrypt_tag_splitting(__m128i M, int mlen, __m128i* C, __m128i L,__m128i V, __m128i* roundkeys);
int decrypt_tag_splitting(__m128i C, int clen, __m128i* M, __m128i L,__m128i V,__m128i tag, __m128i* roundkeys,__m128i* roundkeys_dec);


__m128i pmac(__m128i* in, int inlen, __m128i L, __m128i* roundkeys){
  int i, max;
  __m128i delta0, temp, temp2, V = _mm_setzero_si128();
  delta0 = gf128Mul3(L);
  delta0 = gf128Mul3(delta0);
  delta0 = gf128Mul3(delta0);
  __m128i  mask = _mm_setr_epi16(0x0e0f,0x0c0d,0x0a0b,0x0809,0x0607,0x0405,0x0203,0x0001);
  max = (inlen+15)>>4;
  for(i = 0;i<max-1; i++){
    temp2 = _mm_shuffle_epi8(delta0, mask);
    temp = _mm_xor_si128(temp2, in[i]);
    temp = AES_ECB_encrypt(temp,roundkeys);
    V = _mm_xor_si128(V,temp);
    delta0 = gf128Mul2(delta0);
  }
  if(inlen%16 == 0){
    delta0 = gf128Mul3(delta0);
    temp2 = _mm_shuffle_epi8(delta0, mask);
    temp = _mm_xor_si128(temp2,in[max-1]);
    temp = _mm_xor_si128(V,temp);
    V = AES_ECB_encrypt(temp,roundkeys);
    
  }
  else{
    delta0 = gf128Mul3(delta0);
    delta0 = gf128Mul3(delta0);
    temp2 = _mm_shuffle_epi8(delta0, mask);
    temp = padd(in[max-1],inlen%16);
    temp = _mm_xor_si128(temp2,temp);
    temp = _mm_xor_si128(V,temp);
    V = AES_ECB_encrypt(temp,roundkeys);
  }
  return V;
}

// inline __m128i encrypt(__m128i V, __m128i L, __m128i* M,__m128i* C, int mlen, __m128i* roundkeys ){
// 
//   return S;
// }


void AES_COPA_encrypt(unsigned char* M,int mlen,unsigned char* A, int Alen, unsigned char* N, int Nlen, unsigned char*C,  unsigned char* T , const unsigned char* K)
{
	int i;
	__m128i roundkeys[11];
	__m128i temp, sigma, temp2, temp3,S;
	__m128i  mask = _mm_setr_epi16(0x0e0f,0x0c0d,0x0a0b,0x0809,0x0607,0x0405,0x0203,0x0001);
	roundkeys[0] = _mm_load_si128((__m128i*) K);
	memcpy(A+Alen, N,Nlen);
	AES_128_Key_Expansion(roundkeys);
	__m128i* Cpointer = (__m128i*) C;
	__m128i* Mpointer = (__m128i*) M;
	__m128i L = AES_ECB_encrypt(_mm_setzero_si128(),roundkeys);
	temp3 = _mm_shuffle_epi8(L, mask);

	__m128i V = pmac((__m128i*) A, Alen+Nlen,  temp3,  roundkeys);
// 	printvector(V,"V");

	if(mlen<16){
	  temp = _mm_load_si128((__m128i*) M);
	 temp =  encrypt_tag_splitting(temp,  mlen,Cpointer,  temp3, V, roundkeys);
	 _mm_store_si128((__m128i*) T, temp);
	}
	else{

	//__m128i S = encrypt(V,L,(__m128i*)M,(__m128i*)C,mlen,roundkeys);
		__m128i delta0 = gf128Mul3(temp3);
		__m128i delta1 = gf128Mul2(temp3);
		__m128i temp1;
		S = _mm_xor_si128(L,V);
		sigma = _mm_setzero_si128();
		int max = (mlen)>>4;
		for(i=0;i<max;i++){
			temp2 = _mm_shuffle_epi8(delta0, mask);
			temp1 = _mm_xor_si128(Mpointer[i],temp2);
                        sigma = _mm_xor_si128(sigma,temp1);
			temp2 = AES_ECB_encrypt(temp1,roundkeys);
			S = _mm_xor_si128(S,temp2);
			temp2 = AES_ECB_encrypt(S,roundkeys);
			temp1 = _mm_shuffle_epi8(delta1, mask);
			Cpointer[i] = _mm_xor_si128(temp2,temp1);
			delta0 = gf128Mul2(delta0);
			delta1 = gf128Mul2(delta1);  
	}
	temp = gf128Mul7(temp3);
	temp2 = gf128Mul3(temp3);
	temp2 = gf128Mul3(temp2);
	for( i = 1;i< ((mlen+15)>>4);i++){
		temp = gf128Mul2(temp); 
		temp2 = gf128Mul2(temp2);
	}
	temp2 = _mm_shuffle_epi8(temp2, mask);
	temp = _mm_shuffle_epi8(temp, mask);
// 	printvector(temp,"temp");
// 	printvector(temp2,"temp2");
// 	printvector(sigma,"sigma");
	temp2 = _mm_xor_si128(sigma,temp2);
	temp2 = AES_ECB_encrypt(temp2,roundkeys);
	temp2 = _mm_xor_si128(temp2, S);
	temp2 = AES_ECB_encrypt(temp2,roundkeys);
	temp = _mm_xor_si128(temp2,temp);
	_mm_store_si128((__m128i*) T, temp);}
}

int AES_COPA_decrypt( unsigned char* C,int clen, unsigned char * A, int Alen, unsigned char* N, int Nlen,unsigned char*M,unsigned char* T , const unsigned char* K){
	int i;
	__m128i roundkeys[11];
	__m128i roundkeys_dec[11];
	__m128i  mask = _mm_setr_epi16(0x0e0f,0x0c0d,0x0a0b,0x0809,0x0607,0x0405,0x0203,0x0001);
	__m128i temp, sigma, temp2,temp3;
	__m128i  Torg = _mm_load_si128((__m128i*) T);
	__m128i* Cpointer = (__m128i*) C;
	__m128i* Mpointer = (__m128i*) M;
	memcpy(A+Alen, N,Nlen);
	roundkeys[0] = _mm_load_si128((__m128i*) K);
	AES_128_Key_Expansion (roundkeys);
	AES_Key_Dec(roundkeys, roundkeys_dec);
	__m128i L = AES_ECB_encrypt(_mm_setzero_si128(),roundkeys);
	temp = AES_ECB_decrypt(L,roundkeys_dec);
		temp3 = _mm_shuffle_epi8(L, mask);

	__m128i V = pmac((__m128i*)A, Alen +Nlen,temp3, roundkeys);
// 	printvector(V,"V");


	if(clen<16){
		temp = _mm_load_si128(Cpointer);
		i= decrypt_tag_splitting(temp,  clen,(__m128i*) M,  temp3, V,Torg, roundkeys, roundkeys_dec);
		return i;
	}
//	__m128i S = decrypt(V, L, (__m128i*) C,Mpointer,clen,roundkeys_dec);
	__m128i delta0 = gf128Mul3(temp3);
	__m128i delta1 = gf128Mul2(temp3);
	__m128i S, temp1;
	  int max = (clen)>>4;
	S = _mm_xor_si128(L,V);
	temp1 = AES_ECB_decrypt(L,roundkeys_dec);
	for(i=0;i<max;i++){
		temp2 = _mm_shuffle_epi8(delta1, mask);
		temp1 = _mm_xor_si128(Cpointer[i],temp2);
		temp2 = AES_ECB_decrypt(temp1,roundkeys_dec);
		temp1 = _mm_xor_si128(S,temp2);
		S = temp2;
		temp2 = AES_ECB_decrypt(temp1,roundkeys_dec);
		temp1 = _mm_shuffle_epi8(delta0, mask);
		Mpointer[i] = _mm_xor_si128(temp2, temp1);
		delta0 = gf128Mul2(delta0);
		delta1 = gf128Mul2(delta1);    
	}	
	sigma = _mm_load_si128((__m128i*)M);
	temp = gf128Mul7(temp3);
	temp2 = gf128Mul3(temp3);
	temp2 = gf128Mul3(temp2);
	for(i = 1;i < ((clen+15)>>4);i++){
		sigma = _mm_xor_si128(sigma,Mpointer[i]);
		temp = gf128Mul2(temp); 
		temp2 = gf128Mul2(temp2);
	}
	temp2 = _mm_shuffle_epi8(temp2, mask);
	temp = _mm_shuffle_epi8(temp, mask);
// 	printvector(temp,"temp");
// 	printvector(temp2,"temp2");
// 	printvector(sigma,"sigma");

	temp2 = _mm_xor_si128(sigma,temp2);
	temp2 = AES_ECB_encrypt(temp2,roundkeys);
	temp2 = _mm_xor_si128(temp2, S);
	temp2 = AES_ECB_encrypt(temp2,roundkeys);
	temp = _mm_xor_si128(temp2,temp);
// 	printvector(temp,"tagdec");
	if(_mm_test_all_ones(_mm_cmpeq_epi8(temp,Torg))){ //1 if same, -1 if different
	  return 1;}
	return -1;
}

// __m128i decrypt(__m128i V, __m128i L, __m128i* C,__m128i* M, int mlen, __m128i* roundkeys_dec ){
// 
// 	return S;
// }

__m128i encrypt_tag_splitting(__m128i M, int mlen, __m128i* C, __m128i L,__m128i V, __m128i* roundkeys){
	  __m128i delta36, delta37,delta38,delta236,delta367, S, temp1, temp2, T;
	  __m128i  mask = _mm_setr_epi16(0x0e0f,0x0c0d,0x0a0b,0x0809,0x0607,0x0405,0x0203,0x0001);
	  delta36 = gf128Mul3(L);
	  delta36 = gf128Mul3(delta36);
	  delta36 = gf128Mul3(delta36);
	  delta36 = gf128Mul3(delta36);
	  delta36 = gf128Mul3(delta36);
 	  delta36 = gf128Mul3(delta36);
	  delta37 = gf128Mul3(delta36);
	  delta38 = gf128Mul3(delta37);
	  delta367 = gf128Mul7(delta36);
	  delta236 = gf128Mul2(delta36);
	  delta36 =  _mm_shuffle_epi8(delta36, mask);
	  delta37 = _mm_shuffle_epi8(delta37, mask);
	  delta38 = _mm_shuffle_epi8(delta38, mask);
	  delta367 = _mm_shuffle_epi8(delta367, mask);
	  delta236 = _mm_shuffle_epi8(delta236, mask);
	  M = padd(M,mlen);

	  temp1 = _mm_xor_si128(M,delta37);
	  temp2 = _mm_xor_si128(V,delta36);
	  temp1 = AES_ECB_encrypt(temp1,roundkeys);
	  S = _mm_xor_si128(temp1,temp2);
	  temp1 = AES_ECB_encrypt(S,roundkeys);
	  C[0] = _mm_xor_si128(temp1,delta236);
	    //tag
	  temp1 = _mm_xor_si128(M,delta38);
	  temp2 = AES_ECB_encrypt(temp1,roundkeys);
	  temp1 = _mm_xor_si128(temp2,S);
	  temp2 = AES_ECB_encrypt(temp1,roundkeys);
	  T = _mm_xor_si128(temp2,delta367);
	  return T;  
}

int decrypt_tag_splitting(__m128i C, int clen, __m128i* M, __m128i L,__m128i V,__m128i tag, __m128i* roundkeys,__m128i* roundkeys_dec){
	__m128i delta36, delta37,delta38,delta236,delta367, S, temp1, temp2, T;
	  __m128i  mask = _mm_setr_epi16(0x0e0f,0x0c0d,0x0a0b,0x0809,0x0607,0x0405,0x0203,0x0001);
	  delta36 = gf128Mul3(L);
	  delta36 = gf128Mul3(delta36);
	  delta36 = gf128Mul3(delta36);
	  delta36 = gf128Mul3(delta36);
	  delta36 = gf128Mul3(delta36);
 	  delta36 = gf128Mul3(delta36);
	  delta37 = gf128Mul3(delta36);
	  delta38 = gf128Mul3(delta37);
	  delta367 = gf128Mul7(delta36);
	  delta236 = gf128Mul2(delta36);
	  delta36 =  _mm_shuffle_epi8(delta36, mask);
	  delta37 = _mm_shuffle_epi8(delta37, mask);
	  delta38 = _mm_shuffle_epi8(delta38, mask);
	  delta367 = _mm_shuffle_epi8(delta367, mask);
	  delta236 = _mm_shuffle_epi8(delta236, mask);
	temp1 = _mm_xor_si128(C,delta236);
	S = AES_ECB_decrypt(temp1,roundkeys_dec);
	temp2 = _mm_xor_si128(V,S);
	temp1 = _mm_xor_si128(delta36,temp2);

	temp2 = AES_ECB_decrypt(temp1,roundkeys_dec);

	temp1 = _mm_xor_si128(temp2,delta37);

	_mm_store_si128(M,temp1);
	//  tag
	temp1 = _mm_xor_si128(M[0],delta38);
	temp2 = AES_ECB_encrypt(temp1,roundkeys);
	temp1 = _mm_xor_si128(temp2,S);
	temp2 = AES_ECB_encrypt(temp1,roundkeys);
	T = _mm_xor_si128(temp2,delta367);
	if(_mm_test_all_ones(_mm_cmpeq_epi8(T,tag))){ //1 if same, -1 if different
		return 1;
	}
	return -1;
}



/*GF multiplications*/
__m128i gf128Mul2(__m128i A){

  __m128i test =  _mm_set_epi8(0,0,0,0,0,0,0,0,0x80,0,0,0,0,0,0,0);
  __m128i result = _mm_slli_epi64(A,1);
  if(_mm_test_all_zeros(test, A) == 0){
    test = _mm_set_epi8(0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0);
    result = _mm_xor_si128(result,test);
  }
  
  test = _mm_set_epi8(0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  if(_mm_test_all_zeros(test, A) == 0){
     test = _mm_set_epi8(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x87);
     result = _mm_xor_si128(result,test);
  }

  return result;
}

__m128i gf128Mul3(__m128i A){
  __m128i test =  _mm_set_epi8(0,0,0,0,0,0,0,0,0x80,0,0,0,0,0,0,0);
  __m128i result = _mm_slli_epi64(A,1);
  if(_mm_test_all_zeros(test, A) == 0){
    test = _mm_set_epi8(0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0);
    result = _mm_xor_si128(result,test);
  }
  
  test = _mm_set_epi8(0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  if(_mm_test_all_zeros(test, A) == 0){
     test = _mm_set_epi8(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x87);
     result = _mm_xor_si128(result,test);
  }
  result = _mm_xor_si128(result,A);;
  return result;
}

__m128i gf128Mul7(__m128i A){
  __m128i test =  _mm_set_epi8(0,0,0,0,0,0,0,0,0x80,0,0,0,0,0,0,0);
  __m128i result;
  __m128i temp = _mm_slli_epi64(A,1);
  if(_mm_test_all_zeros(test, A) == 0){
    test = _mm_set_epi8(0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0);
    temp = _mm_xor_si128(temp,test);
  }
  
  test = _mm_set_epi8(0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  if(_mm_test_all_zeros(test, A) == 0){
     test = _mm_set_epi8(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x87);
     temp = _mm_xor_si128(temp,test);
  }  
   result = _mm_slli_epi64(temp,1);
  if(_mm_test_all_zeros(test, temp) == 0){
    test = _mm_set_epi8(0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0);
    result = _mm_xor_si128(result,test);
  }
  
  test = _mm_set_epi8(0x80,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  if(_mm_test_all_zeros(test, temp) == 0){
     test = _mm_set_epi8(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x87);
     result = _mm_xor_si128(result,test);
  }
  result = _mm_xor_si128(result,temp);
  result = _mm_xor_si128(result,A);
  return result;
}

/*AES*/
//key expansion
inline void AES_Key_Dec( __m128i* enc_key, __m128i* dec_key)
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

inline __m128i padd(__m128i P, int length){
	__m128i result,b, mask;
	switch(length){
	  case 1:
	    mask = _mm_set_epi8(255,255,255,255,255 ,255,255,255,255 ,255,255,255,255 ,255,255,0);
	    b = _mm_set_epi8(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0x80,0);
	    result = _mm_blendv_epi8(P,b,mask);
	    break;
	  case 2:
	    mask = _mm_set_epi8(255,255,255,255,255 ,255,255,255,255 ,255,255,255,255 ,255,0,0);
	    b = _mm_set_epi8(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0x80,0,0);
	    result = _mm_blendv_epi8(P,b,mask);  
	    break;
	  case 3:
	    mask = _mm_set_epi8(255,255,255,255,255 ,255,255,255,255 ,255,255,255,255 ,0,0,0);
	    b = _mm_set_epi8(0,0,0,0, 0,0,0,0, 0,0,0,0, 0x80,0,0,0);
	    result = _mm_blendv_epi8(P,b,mask);
	    break;
	  case 4:
	    mask = _mm_set_epi8(255,255,255,255,255 ,255,255,255,255 ,255,255,255,0,0,0,0);
	    b = _mm_set_epi8(0,0,0,0, 0,0,0,0, 0,0,0,0x80, 0,0,0,0);
	    result = _mm_blendv_epi8(P,b,mask);
	    break;
	  case 5:
	    mask = _mm_set_epi8(255,255,255,255,255 ,255,255,255,255 ,255,255,0,0,0,0,0);
	    b = _mm_set_epi8(0,0,0,0, 0,0,0,0, 0,0,0x80,0, 0,0,0,0);
	    result = _mm_blendv_epi8(P,b,mask);
	    break;
	  case 6:
	    mask = _mm_set_epi8(255,255,255,255,255 ,255,255,255,255 ,255,0,0,0 ,0,0,0);
	    b = _mm_set_epi8(0,0,0,0, 0,0,0,0, 0,0x80,0,0, 0,0,0,0);
	    result = _mm_blendv_epi8(P,b,mask);
	    break;
	  case 7:
	    mask = _mm_set_epi8(255,255,255,255,255 ,255,255,255,255 ,0,0,0,0 ,0,0,0);
	    b = _mm_set_epi8(0,0,0,0, 0,0,0,0, 0x80,0,0,0, 0,0,0,0);
	    result = _mm_blendv_epi8(P,b,mask);     
	    break;
	  case 8:
	    mask = _mm_set_epi8(255,255,255,255,255 ,255,255,255,0 ,0,0,0,0 ,0,0,0);
	    b = _mm_set_epi8(0,0,0,0, 0,0,0,0x80, 0,0,0,0, 0,0,0,0);
	    result = _mm_blendv_epi8(P,b,mask);
	    break;
	  case 9:
	    mask = _mm_set_epi8(255,255,255,255,255 ,255,255,0,0 ,0,0,0,0 ,0,0,0);
	    b = _mm_set_epi8(0,0,0,0, 0,0,0x80,0, 0,0,0,0, 0,0,0,0);
	    result = _mm_blendv_epi8(P,b,mask);
	    break;
	  case 10:
	    mask = _mm_set_epi8(255,255,255,255,255 ,255,0,0,0 ,0,0,0,0 ,0,0,0);
	    b = _mm_set_epi8(0,0,0,0, 0,0x80,0,0, 0,0,0,0, 0,0,0,0);
	    result = _mm_blendv_epi8(P,b,mask);
	    break;
	  case 11:
	    mask = _mm_set_epi8(255,255,255,255,255 ,0,0,0,0 ,0,0,0,0 ,0,0,0);
	    b = _mm_set_epi8(0,0,0,0, 0x80,0,0,0, 0,0,0,0, 0,0,0,0);
	    result = _mm_blendv_epi8(P,b,mask);
	    break;
	  case 12:
	    mask = _mm_set_epi8(255,255,255,255,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0);
	    b = _mm_set_epi8(0,0,0,0x80, 0,0,0,0, 0,0,0,0, 0,0,0,0);
	    result = _mm_blendv_epi8(P,b,mask);
	    break;
	  case 13:
	    mask = _mm_set_epi8(255,255,255,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0);
	    b = _mm_set_epi8(0,0,0x80,0, 0,0,0,0, 0,0,0,0, 0,0,0,0);
	    result = _mm_blendv_epi8(P,b,mask);
	    break;
	  case 14:
	    mask = _mm_set_epi8(255,255,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0);
	    b = _mm_set_epi8(0,0x80,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0);
	    result = _mm_blendv_epi8(P,b,mask);
	    break;
	  case 15:
	    mask = _mm_set_epi8(255,0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0);
	    b = _mm_set_epi8(0x80,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0);
	    result = _mm_blendv_epi8(P,b,mask);
	    break;
	  default:
	    result = P;
	}
	return result;
}

// void XLS(__m128i* M, __m128i* C,  __m128i delta,  unsigned int s, __m128i roundkeys){
//   __m128i delta3,temp1,temp2,ones;
//   delta = gf128Mul7(delta);
//   delta = gf128Mul7(delta);
//   delta3 = gf128Mul3(delta);
//   temp1 = _mm_xor_si128(M[0],delta3);
//   temp2 = AES_ECB_encrypt(temp1,roundkeys);
//   temp1 = _mm_xor_si128(temp2,delta3);
//   temp2 = mix;
//   
// }
// 
// __m128i mix(__m128i in, int s){
//   __m128i test =  _mm_set_epi8(0,0,0,0,0,0,0,0,0x80,0,0,0,0,0,0,0);
//   __m128i temp = _mm_slli_epi64(A,1);
//   if(_mm_test_all_zeros(test, A) == 0){
//     test = _mm_set_epi8(0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0);
//     temp = 
//   
// }
