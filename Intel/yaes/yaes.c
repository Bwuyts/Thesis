#include "wmmintrin.h"
#include "smmintrin.h"
//#include "aes.h"
#include <stdio.h>
//#include "print.h"
void YAES128_ENC(unsigned char* roundkeys,const unsigned char *N, const unsigned char *A, unsigned char *M, unsigned char *C, unsigned char *T, int Tau, int lengthM, int lengthA, int lengthN);
int YAES128_DEC(const unsigned char* K,const unsigned char *N,const unsigned char *A, unsigned char *M, unsigned char *C, unsigned char *T, int Tau, int lengthM, int lengthA, int lengthN);
inline __m128i Ad128(__m128i *A,int lengthA, __m128i* roundkeys);
inline __m128i EF128(__m128i *N,__m128i *M, int lengthM, __m128i * C, __m128i* roundkeys);
inline __m128i DF128(__m128i *N,__m128i *C, int lengthC, int lengthN, __m128i* M, __m128i* roundkeys);
inline __m128i padd(__m128i P, int length);
inline __m128i x_mult(__m128i A);
inline __m128i AES_ECB_encrypt(const __m128i in,const __m128i *key);
void AES_128_Key_Expansion (__m128i* Key_Schedule);
void initialise(unsigned char* roundkeys , const unsigned char* K){
    
    __m128i* RK = (__m128i*) roundkeys;
    RK[0] = _mm_load_si128((__m128i*) K);
    AES_128_Key_Expansion(RK);
}
//encryption via Yaes
void YAES128_ENC(unsigned char* roundkeys,const unsigned char *N,const unsigned char *A, unsigned char *M, unsigned char *C, unsigned char *T, int Tau, int lengthM, int lengthA, int lengthN){
  __m128i TA, TE;

  
  //compute TA using TA if adata is given, else 0 
  if(lengthA>0){
    TA = Ad128((__m128i*)A,lengthA, roundkeys);
  }
  else{
    TA =_mm_setzero_si128();
  }
  //compute tag and cyphertext
  TE = EF128((__m128i*)N,(__m128i*) M,lengthM,(__m128i*) C, roundkeys);
  //set tag
  TE = _mm_xor_si128(TA,TE); 
  _mm_store_si128( (__m128i*) T, TE);
}
//decryption via Yaes
int YAES128_DEC(const unsigned char* K,const unsigned char *N, const unsigned char *A, unsigned char *M, unsigned char *C, unsigned char *T, int Tau, int lengthM, int lengthA, int lengthN){
  __m128i TA, TE,Torg,Tnew;
  __m128i roundkeys[11];
  roundkeys[0] = _mm_load_si128((__m128i*) K);
  AES_128_Key_Expansion(roundkeys);
  Torg = _mm_load_si128((__m128i*) T);
  if(lengthA>0){
    TA = Ad128((__m128i*)A,lengthA, roundkeys);
  }
  else{
    TA = _mm_setzero_si128();
  }
  TE = DF128((__m128i*)N,(__m128i*) C,lengthM,lengthN,(__m128i*) M, roundkeys) ;
  Tnew = _mm_xor_si128(TA,TE);

  if(_mm_test_all_ones(_mm_cmpeq_epi8(Tnew,Torg))){ //0 if same, 1 if different
	  return 1;}
  return -1;
}

//EF function
inline __m128i EF128(__m128i *N,__m128i *M, int lengthM, __m128i * C, __m128i* roundkeys){
  int m,i;
  __m128i L, S, V, temp,temp2,mask;
  //mask needed to perform x_mult.
  mask = _mm_setr_epi16(0x0e0f,0x0c0d,0x0a0b,0x0809,0x0607,0x0405,0x0203,0x0001);
  m=(lengthM)>>4;
  temp2 = N[0];
  temp = _mm_set_epi8(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  temp2 = _mm_xor_si128(temp,temp2);
  L = AES_ECB_encrypt(temp2,roundkeys);
  S=_mm_setzero_si128();
  L = _mm_shuffle_epi8(L, mask);
  for(i=0;i<m;i++){
      //V = AES128rRounds(L, 1, 6);
      temp2 = _mm_shuffle_epi8(L, mask);
      V = _mm_aesenc_si128(temp2,roundkeys[1]);
      V = _mm_aesenc_si128(V,roundkeys[2]);
      V = _mm_aesenc_si128(V,roundkeys[3]);
      V = _mm_aesenc_si128(V,roundkeys[4]);
      V = _mm_aesenc_si128(V,roundkeys[5]);
      V = _mm_aesenc_si128(V,roundkeys[6]);
      temp = M[i];

      V = _mm_xor_si128(V,temp);
      //temp = AES128rRounds(V, 7, 4);
      temp = _mm_aesenc_si128(V,roundkeys[7]);
      temp = _mm_aesenc_si128(temp,roundkeys[8]);
      temp = _mm_aesenc_si128(temp,roundkeys[9]);
      temp = _mm_aesenc_si128(temp,roundkeys[10]);
      S = _mm_xor_si128(S,temp);
      temp = _mm_xor_si128(V,temp2);

      C[i]=temp;
      L = x_mult(L);
  }
  //if length is not a multiple of 16 bytes
      if(lengthM%16 !=0){
      temp2 = _mm_shuffle_epi8(L, mask);
      V = _mm_aesenc_si128(temp2,roundkeys[1]);
      V = _mm_aesenc_si128(V,roundkeys[2]);
      V = _mm_aesenc_si128(V,roundkeys[3]);
      V = _mm_aesenc_si128(V,roundkeys[4]);
      V = _mm_aesenc_si128(V,roundkeys[5]);
      V = _mm_aesenc_si128(V,roundkeys[6]);
      temp = M[i];
	temp = padd(temp,lengthM%16);
      V = _mm_xor_si128(V,temp);
      //temp = AES128rRounds(V, 7, 4);
      temp = _mm_aesenc_si128(V,roundkeys[7]);
      temp = _mm_aesenc_si128(temp,roundkeys[8]);
      temp = _mm_aesenc_si128(temp,roundkeys[9]);
      temp = _mm_aesenc_si128(temp,roundkeys[10]);
      S = _mm_xor_si128(S,temp);
      temp = _mm_xor_si128(V,temp2);
 	temp = padd(temp,lengthM%16);
      C[i]=temp;
      L = x_mult(L);}
  if(lengthM%16 != 0 || lengthM==0){
      temp = x_mult(L);
      temp = x_mult(temp);
      L = _mm_xor_si128(temp,L);
      //L*(x^2+1)
  }else{
      temp = x_mult(L);
      //L*(x+1)
      L = _mm_xor_si128(temp,L);// L=L*(x+1)
  }
  temp2 = _mm_shuffle_epi8(L,mask);
  temp = _mm_xor_si128(S,temp2);
  return AES_ECB_encrypt(temp,roundkeys);
}

inline __m128i DF128(__m128i *N,__m128i *C, int lengthC, int lengthN, __m128i * M, __m128i* roundkeys){
   int c,i;
  __m128i L, S, V, temp,temp2,mask;
  mask = _mm_setr_epi8(0x0f,0x0e,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00);
  c=(lengthC)>>4;
  temp2 = N[0];
  temp = _mm_set_epi8(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  temp2 = _mm_xor_si128(temp,temp2);
  L = AES_ECB_encrypt(temp2,roundkeys);
  S=_mm_setzero_si128();
  L = _mm_shuffle_epi8(L, mask);

  for(i=0;i<c;i++){
  //  V = AES128rRounds(L, 1, 6);
     temp2 = _mm_shuffle_epi8(L, mask);
     //aes[6]rounds
     V = _mm_aesenc_si128(temp2,roundkeys[1]);
     V = _mm_aesenc_si128(V,roundkeys[2]);
     V = _mm_aesenc_si128(V,roundkeys[3]);
     V = _mm_aesenc_si128(V,roundkeys[4]);
     V = _mm_aesenc_si128(V,roundkeys[5]);
     V = _mm_aesenc_si128(V,roundkeys[6]);
    temp = _mm_xor_si128(V,temp2);
    temp2 = C[i];
    temp2 = _mm_xor_si128(temp2, temp );
    _mm_store_si128(M+i,temp2);
    V = _mm_xor_si128(V,temp2);
    //aes[4]rounds
     temp = _mm_aesenc_si128(V,roundkeys[7]);
     temp = _mm_aesenc_si128(temp,roundkeys[8]);
     temp = _mm_aesenc_si128(temp,roundkeys[9]);
     temp = _mm_aesenc_si128(temp,roundkeys[10]);
    S = _mm_xor_si128(S,temp);
    L = x_mult(L);
  }
  if(lengthC%16!=0){
     temp2 = _mm_shuffle_epi8(L, mask);
     V = _mm_aesenc_si128(temp2,roundkeys[1]);
     V = _mm_aesenc_si128(V,roundkeys[2]);
     V = _mm_aesenc_si128(V,roundkeys[3]);
     V = _mm_aesenc_si128(V,roundkeys[4]);
     V = _mm_aesenc_si128(V,roundkeys[5]);
     V = _mm_aesenc_si128(V,roundkeys[6]);
     temp = _mm_xor_si128(V,temp2);
     temp2 = C[i];
     temp2 = padd(temp2,lengthC%16);
     temp2 = _mm_xor_si128(temp2, temp );
     temp2 = padd(temp2,lengthC%16);
     _mm_store_si128(M+i,temp2);
     V = _mm_xor_si128(V,temp2);
     //aes[4]rounds
     temp = _mm_aesenc_si128(V,roundkeys[7]);
     temp = _mm_aesenc_si128(temp,roundkeys[8]);
     temp = _mm_aesenc_si128(temp,roundkeys[9]);
     temp = _mm_aesenc_si128(temp,roundkeys[10]);
    S = _mm_xor_si128(S,temp);
    L = x_mult(L);}
    
  if(lengthC%16 != 0||lengthC==0){
      temp = x_mult(L);
      temp = x_mult(temp);
      L = _mm_xor_si128(temp,L);
      //L*(x^2+1)
  }else{
      temp = x_mult(L);
      //L*(x+1)
      L = _mm_xor_si128(temp,L);// L=L*(x+1)
  }
  temp2 = _mm_shuffle_epi8(L,mask);
  temp = _mm_xor_si128(S,temp2);
  return AES_ECB_encrypt(temp,roundkeys);
}
inline __m128i Ad128(__m128i *A,int lengthA, __m128i* roundkeys){//length in bytes
  __m128i R, S, V,temp,temp2, mask;
  mask = _mm_setr_epi8(0x0f,0x0e,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00);
  int i,a;
  a=(lengthA)>>4;
  S =_mm_setzero_si128();
  R = AES_ECB_encrypt(S,roundkeys);
  R = _mm_shuffle_epi8(R, mask);
  for(i=0;i<a;i++){
    temp2 = _mm_shuffle_epi8(R,mask);
    temp =_mm_load_si128(A+i);

    V = _mm_xor_si128(temp,temp2);
    //AES128[4]Rounds
     temp = _mm_aesenc_si128(V,roundkeys[1]);
     temp = _mm_aesenc_si128(temp,roundkeys[2]);
     temp = _mm_aesenc_si128(temp,roundkeys[3]);
     temp = _mm_aesenc_si128(temp,roundkeys[4]);
    S = _mm_xor_si128(S,temp);
    R = x_mult(R);
  }
  if(lengthA%16!=0){
      temp2 = _mm_shuffle_epi8(R,mask);
      temp =_mm_load_si128(A+i);
      temp = padd(temp,lengthA%16);
      V = _mm_xor_si128(temp,temp2);
	//AES128[4]Rounds
      temp = _mm_aesenc_si128(V,roundkeys[1]);
      temp = _mm_aesenc_si128(temp,roundkeys[2]);
      temp = _mm_aesenc_si128(temp,roundkeys[3]);
      temp = _mm_aesenc_si128(temp,roundkeys[4]);
    S = _mm_xor_si128(S,temp);
    R = x_mult(R);
  }
  if(lengthA%16 != 0){
    temp = x_mult(R);
    temp = x_mult(temp);
    R= _mm_xor_si128(temp,R);
  }else{
    temp = x_mult(R);
    R= _mm_xor_si128(temp,R);
  }
  temp2 = _mm_shuffle_epi8(R,mask);
  temp = _mm_xor_si128(S,temp2);
  return AES_ECB_encrypt(temp,roundkeys);
}

inline __m128i x_mult(__m128i A){
  __m128i result,test;
  result = _mm_srli_epi64 (A, 1);
  test = _mm_set_epi8(0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0);
  if(_mm_test_all_zeros(test, A) == 0){
    test = _mm_set_epi8(0,0,0,0,0,0,0,0,128,0,0,0,0,0,0,0);
    result = _mm_xor_si128(result,test);
  }
  test = _mm_set_epi8(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1);
  if(_mm_test_all_zeros(test, A) == 0){
     test = _mm_set_epi8(0xE1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
     result = _mm_xor_si128(result,test);
  }
  return result;
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

