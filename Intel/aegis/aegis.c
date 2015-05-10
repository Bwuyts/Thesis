#include "wmmintrin.h"
#include "smmintrin.h"
#include <stdio.h>
#include <stdint.h>
	#include "print.h"

inline void initialize(const unsigned char* key, unsigned char* IV, __m128i* state);
inline void stateupdate128(__m128i message, __m128i* state);
inline void encrypt(const unsigned char* key, unsigned char* IV,unsigned char* Adata, unsigned char* plain, unsigned char* cipher, unsigned char* tag,uint64_t adlen,uint64_t msglen);
inline int decrypt(const unsigned char* key, unsigned char* IV,unsigned char* Adata, unsigned char* cipher, unsigned char* plain, unsigned char* tag, uint64_t adlen,uint64_t msglen);
inline void ADprocessing(__m128i* A, int64_t adlen, __m128i* state);
inline void aegis128Encrypt(__m128i* M,__m128i* C,uint64_t msglen, __m128i* state);
inline void aegis128Decrypt(__m128i* C,__m128i* M,uint64_t msglen, __m128i* state);
inline __m128i padd(__m128i P, int length);
inline __m128i finalize(uint64_t msglen,uint64_t adlen, __m128i* state);


inline void stateupdate128(__m128i message, __m128i* state){
  __m128i tmp,tmp2;
    tmp =  state[4];
    tmp2 = _mm_xor_si128 (state[0],message);
    state[4] = _mm_aesenc_si128 (state[3],state[4]);    
    state[3] = _mm_aesenc_si128 (state[2],state[3]);    
    state[2] = _mm_aesenc_si128 (state[1],state[2]);
    state[1] = _mm_aesenc_si128 (state[0],state[1]);
    state[0] = _mm_aesenc_si128 (tmp,tmp2);
    //state[0] = _mm_xor_si128 (tmp,message);
}

inline void encrypt(const unsigned char* key, unsigned char* IV,unsigned char* Adata, unsigned char* plain, unsigned char* cipher, unsigned char* tag,uint64_t adlen,uint64_t msglen){
  __m128i T;
  __m128i state[5] = {{0}};
  initialize(key,IV, state);
  if(adlen !=0){
    ADprocessing((__m128i*) Adata, adlen,state);
  }

  aegis128Encrypt((__m128i*) plain,(__m128i*) cipher,msglen,state);
  T = finalize(msglen,adlen,state);
  _mm_store_si128((__m128i*) tag, T);
}

inline int decrypt(const unsigned char* key, unsigned char* IV,unsigned char* Adata, unsigned char* cipher, unsigned char* plain, unsigned char* tag, uint64_t adlen,uint64_t msglen){
  __m128i Torg,T;
  __m128i state[5] = {{0}};
    initialize(key,IV, state);

  Torg = _mm_loadu_si128((__m128i*) tag);
  if(adlen !=0){
  ADprocessing((__m128i*) Adata, adlen,state);

  }
  aegis128Decrypt((__m128i*) cipher,(__m128i*) plain,msglen,state);
  T = finalize(msglen,adlen,state);
  if(_mm_test_all_ones(_mm_cmpeq_epi8(T, Torg))){
    return 1;}
  return -1;

}


inline void initialize(const unsigned char* key, unsigned char* IV, __m128i* state){
  __m128i K,IVreg,tmp,KxorIV;
  K = _mm_load_si128((__m128i*) key);
  IVreg = _mm_load_si128((__m128i*) IV);
  //load iv and key into state:
  KxorIV = _mm_xor_si128 (K,IVreg);
  state[0]= KxorIV;
  state[1] = _mm_set_epi8(0xdd,0x28,0xb5,0x73,0x42,0x31,0x11,0x20,0xf1,0x2f,0xc2,0x6d,0x55,0x18,0x3d,0xdb);
  state[2] = _mm_set_epi8(0x62,0x79,0xe9,0x90,0x59,0x37,0x22,0x15,0x0d,0x08,0x05,0x03,0x02,0x01,0x1, 0x0);
  tmp = _mm_xor_si128 (K,state[2]);
  _mm_store_si128(state+3,tmp);
  tmp = _mm_xor_si128 (K,state[1]);
  _mm_store_si128(state+4,tmp);
//     Perform 10 state updates
    stateupdate128(K,state);
    stateupdate128(KxorIV,state);
    stateupdate128(K,state);
    stateupdate128(KxorIV,state);
    stateupdate128(K,state);
    stateupdate128(KxorIV,state);
    stateupdate128(K,state);
    stateupdate128(KxorIV,state);
    stateupdate128(K,state);
    stateupdate128(KxorIV,state);
}


inline void ADprocessing(__m128i* A, int64_t adlen, __m128i* state){
  uint64_t i;
  __m128i ADi;
  uint64_t max = (adlen+15)/16;
  for(i=0;i<max;i++){
    ADi = _mm_load_si128(A+i);
    if(adlen%16 != 0 && i == max-1){
      padd(ADi,adlen%16);
    }
    stateupdate128(ADi,state);
  } 
}

inline void aegis128Encrypt(__m128i* M,__m128i* C,uint64_t msglen, __m128i* state){
  __m128i tmp1, tmp2, tmp3,Mi;
  uint64_t i;
  uint64_t max = (msglen)>>4;
  for(i=0;i<max;i++){
    Mi = _mm_load_si128(M+i);
    tmp1 =  _mm_and_si128 (state[2],state[3]);
    tmp2 = _mm_xor_si128(state[1],state[4]);
    tmp3 = _mm_xor_si128(tmp1,tmp2);
    tmp1 = _mm_xor_si128(tmp3,Mi);
    _mm_store_si128(C+i,tmp1);
    stateupdate128(Mi,state);  
  }
  if(msglen%16 != 0){
    Mi = _mm_load_si128(M+i);
    tmp1 =  _mm_and_si128 (state[2],state[3]);
    tmp2 = _mm_xor_si128(state[1],state[4]);
    tmp3 = _mm_xor_si128(tmp1,tmp2);
      padd(Mi,msglen%16);
    tmp1 = _mm_xor_si128(tmp3,Mi);
    _mm_store_si128(C+i,tmp1);
    stateupdate128(Mi,state);
  }
}

inline __m128i finalize(uint64_t msglen,uint64_t adlen, __m128i* state){
  __m128i tmp, T;
  tmp = _mm_set_epi64x(msglen<<3,adlen<<3);
  tmp = _mm_xor_si128(tmp, state[3]);
  stateupdate128(tmp,state);
  stateupdate128(tmp,state);
  stateupdate128(tmp,state);
  stateupdate128(tmp,state);
  stateupdate128(tmp,state);
  stateupdate128(tmp,state);
  stateupdate128(tmp,state);
  
  tmp = _mm_xor_si128(state[0],state[1]);
  T= _mm_xor_si128(state[2],state[3]);
  tmp = _mm_xor_si128(tmp, state[4]);
  T = _mm_xor_si128(tmp, T);
  return T;
  
}

inline void aegis128Decrypt(__m128i* C,__m128i* M,uint64_t msglen, __m128i* state){
  __m128i tmp1, tmp2, tmp3,Ci;
  uint64_t i;
  uint64_t max = (msglen)>>4;

  for(i=0;i<max;i++){
    Ci = _mm_load_si128(C+i);
    tmp1 = _mm_and_si128 (state[2],state[3]);
    tmp2 = _mm_xor_si128(state[1],state[4]);
    tmp3 = _mm_xor_si128(tmp1,tmp2);
    tmp1 = _mm_xor_si128(tmp3,Ci);
    _mm_store_si128(M+i,tmp1);
    stateupdate128(tmp1,state);
  }
  //deal with the partial block
  if(msglen%16 != 0){
    Ci = _mm_load_si128(C+i);
    tmp1 = _mm_and_si128 (state[2],state[3]);
    tmp2 = _mm_xor_si128(state[1],state[4]);
    tmp3 = _mm_xor_si128(tmp1,tmp2);
    padd(Ci,msglen%16);
    tmp1 = _mm_xor_si128(tmp3,Ci);
    _mm_store_si128(M+i,tmp1);
    stateupdate128(tmp1,state);
  }
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

