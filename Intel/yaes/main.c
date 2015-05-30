#include "yaes.h"
#include "print.h"
#include <stdio.h>
#include "wmmintrin.h" 
#include "smmintrin.h"
// #define lengthA 0
// #define lengthN 16
// #define lengthT 16
// #define lengthM 0
// const unsigned char key[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
// const unsigned char adata[lengthA];
// const unsigned char nonce[16] = {0x09,0xf9,0x11,0x02,0x9d,0x74,0xe3,0x5b,0xd8,0x41,0x56,0xc5,0x63,0x56,0x88,0xc0};
// unsigned char plain[lengthM];
// unsigned char cipher[lengthM];
// unsigned char tag[lengthT] = {0xf6 ,0x2f ,0x04 ,0x0d ,0x7c ,0x7c,0xc3 ,0x0b ,0xfc ,0xf4,0x49 ,0xfb ,0x1f ,0xd6 ,0xfb ,0x8c};
// #define lengthA 10
// #define lengthN 16
// #define lengthT 16
// #define lengthM 1
// const unsigned char key[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
// const unsigned char adata[lengthA] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99};
// const unsigned char nonce[16] = {0x09,0xf9,0x11,0x02,0x9d,0x74,0xe3,0x5b,0xd8,0x41,0x56,0xc5,0x63,0x56,0x88,0xc0};
// unsigned char plain[lengthM];// = {0x8e};
// unsigned char cipher[lengthM] = {0xc0};
// unsigned char tag[lengthT] = {0x16,0x39,0x24,0xce,0x11,0xd8,0x1c,0x2d,0x37,0x3a,0x86,0xe6,0x82,0x5e,0x4e,0xfb};
// #define lengthA 16
// #define lengthN 16
// #define lengthT 16
// #define lengthM 16
// const unsigned char key[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
// const unsigned char adata[lengthA] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
// const unsigned char nonce[16] = {0x09,0xf9,0x11,0x02,0x9d,0x74,0xe3,0x5b,0xd8,0x41,0x56,0xc5,0x63,0x56,0x88,0xc0};
// unsigned char plain[lengthM];// = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
// unsigned char cipher[lengthM] = {0x4e,0x23,0xb0,0xf5,0xe5,0x9a,0xac,0xa5,0x55,0x50,0x7f,0x24,0x6a,0xc4,0x85,0x9e};
// unsigned char tag[lengthT] = {0x7d,0x6f,0x15,0x49,0x74,0x1a,0x21,0x77,0x6c,0x21,0x94,0x11,0x34,0x92,0x72,0xa7};

//  #define lengthA 16
//  #define lengthN 16
//  #define lengthT 16
//  #define lengthM 16
//  const unsigned char key[16] = {0x7f,0x7e,0x7d,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x70};
//  const unsigned char adata[lengthA] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
//  const unsigned char nonce[16] = {0x09,0xf9,0x11,0x02,0x9d,0x74,0xe3,0x5b,0xd8,0x41,0x56,0xc5,0x63,0x56,0x88,0xc0};
//  unsigned char plain[lengthM];// = {0x74,0x68,0x69,0x73,0x20,0x69,0x73,0x20,0x73,0x6f,0x6d,0x65,0x20,0x70,0x6c,0x61};
//  unsigned char cipher[lengthM] ={0x63,0xbb,0x6f,0xef,0x9b,0x32,0x10,0xaa,0x76,0x0d,0xd2,0x84,0xc1,0xb0,0x5e,0x55};
//  unsigned char tag[lengthT] = {0x92,0xca ,0x38,0x16 ,0x0c,0x25 ,0xc0,0x9c ,0xab,0xfd ,0x2c,0xc4 ,0x51,0x0a ,0x28,0x61};

 #define lengthA 26
 #define lengthN 16
 #define lengthT 16
 #define lengthM 26
 const unsigned char key[16] = {0x7f,0x7e,0x7d,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x70};
 const unsigned char adata[lengthA] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0xff,0xee,0xdd,0xcc,0xbb,0xaa,0x99,0x88,0x77,0x66};
 const unsigned char nonce[16] = {0x09,0xf9,0x11,0x02,0x9d,0x74,0xe3,0x5b,0xd8,0x41,0x56,0xc5,0x63,0x56,0x88,0xc0};
 unsigned char plain[lengthM] =  {0x74,0x68,0x69,0x73,0x20,0x69,0x73,0x20,0x73,0x6f,0x6d,0x65,0x20,0x70,0x6c,0x61,0x69,0x6e,0x74,0x65,0x78,0x74,0x20,0x74,0x6f,0x20};
 unsigned char cipher[lengthM];// = {0x63,0xbb ,0x6f,0xef ,0x9b,0x32 ,0x10,0xaa ,0x76,0x0d ,0xd2,0x84 ,0xc1,0xb0 ,0x5e,0x55 ,0x39,0x61 ,0xd8,0x27 ,0xb9,0x14 ,0x0b,0xa5 ,0xde,0xc5};
 unsigned char decrypt[lengthM];
unsigned char tag[lengthT];//={0x83,0x94 ,0x67,0x36 ,0x08,0x64 ,0x61,0xfd ,0x3c,0xae ,0xa2,0x51 ,0x7a,0xba ,0x89,0xc4};


int main(){
  int succes;
  unsigned char roundkeys[16*11];

  initialise(roundkeys, key);
  printchar((unsigned char*) roundkeys[0],16,"key");
  printchar((unsigned char*) adata,lengthA,"adata");
  printchar((unsigned char*) nonce,lengthN,"nonce");
  printchar(plain,lengthM,"plain");
  printchar(cipher,lengthM,"cipher");
  YAES128_ENC(roundkeys,nonce,adata,plain,cipher,tag,lengthT, lengthM, lengthA, lengthN);
  printf("Encrypting Done\n");
  printchar(cipher,lengthM,"cipher");
  printchar(tag,lengthT,"tag");
  succes = YAES128_DEC(key,nonce,adata,decrypt,cipher,tag,lengthT, lengthM, lengthA, lengthN);
  printf("Decrypting Done,succes:%i\n",succes); 
  printchar(decrypt,lengthM,"decrypt");


return 0;

}



