#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "aes.h"
#include "encrypt.h"
// #define lengthA 10
// #define lengthN 16
// #define lengthT 16
// #define lengthM 1
// const unsigned char key[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//  unsigned char adata[lengthA] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99};
//  unsigned char nonce[16] = {0x09,0xf9,0x11,0x02,0x9d,0x74,0xe3,0x5b,0xd8,0x41,0x56,0xc5,0x63,0x56,0x88,0xc0};
// unsigned char plain[lengthM] = {0x8e};
//  unsigned char cipher[lengthM];// = {0xc0};
// #define lengthA 16
// #define lengthN 16
// #define lengthT 16
// #define lengthM 16
// const unsigned char key[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
// const unsigned char adata[lengthA] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
// const unsigned char nonce[16] = {0x09,0xf9,0x11,0x02,0x9d,0x74,0xe3,0x5b,0xd8,0x41,0x56,0xc5,0x63,0x56,0x88,0xc0};
// unsigned char plain[lengthM] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
// unsigned char cipher[lengthM];// = {0x4e,0x23,0xb0,0xf5,0xe5,0x9a,0xac,0xa5,0x55,0x50,0x7f,0x24,0x6a,0xc4,0x85,0x9e};
// = {0x4e,0x23,0xb0,0xf5,0xe5,0x9a,0xac,0xa5,0x55,0x50,0x7f,0x24,0x6a,0xc4,0x85,0x9e};
//unsigned char decrypted[lengthM];// = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff};
//unsigned char tag[lengthT];
   #define lengthA 16
   #define lengthN 16
   #define lengthT 16
   #define lengthM 16
   const unsigned char key[16] = {0x7f,0x7e,0x7d,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x70};
   unsigned char plain[lengthM] = {0x74,0x68,0x69,0x73,0x20,0x69,0x73,0x20,0x73,0x6f,0x6d,0x65,0x20,0x70,0x6c,0x61};
   unsigned char cipher[lengthM];// ={0x63,0xbb,0x6f,0xef,0x9b,0x32,0x10,0xaa,0x76,0x0d,0xd2,0x84,0xc1,0xb0,0x5e,0x55};

// #define lengthA 26
// #define lengthN 16
// #define lengthT 16
// #define lengthM 26
// const unsigned char key[16] = {0x7f,0x7e,0x7d,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x70};
// unsigned char adata[lengthA] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0xff,0xee,0xdd,0xcc,0xbb,0xaa,0x99,0x88,0x77,0x66};
// unsigned char nonce[16] = {0x09,0xf9,0x11,0x02,0x9d,0x74,0xe3,0x5b,0xd8,0x41,0x56,0xc5,0x63,0x56,0x88,0xc0};
// unsigned char plain[lengthM] =  {0x74,0x68,0x69,0x73,0x20,0x69,0x73,0x20,0x73,0x6f,0x6d,0x65,0x20,0x70,0x6c,0x61,0x69,0x6e,0x74,0x65,0x78,0x74,0x20,0x74,0x6f,0x20};
// unsigned char cipher[lengthM];// = {0x63,0xbb ,0x6f,0xef ,0x9b,0x32 ,0x10,0xaa ,0x76,0x0d ,0xd2,0x84 ,0xc1,0xb0 ,0x5e,0x55 ,0x39,0x61 ,0xd8,0x27 ,0xb9,0x14 ,0x0b,0xa5 ,0xde,0xc5};

  // unsigned char tag[lengthT];//={0x83,0x94 ,0x67,0x36 ,0x08,0x64 ,0x61,0xfd ,0x3c,0xae ,0xa2,0x51 ,0x7a,0xba ,0x89,0xc4};

	unsigned char decrypted[lengthM];


int main(){
  int succes;
        AES_KEY expkeyp;
        AES_KEY* expkey = &expkeyp;
        AES_set_encrypt_key(k,128,expkey);
        AES_KEY expkeydp;
        AES_KEY* expkeyd = &expkeydp;
        AES_set_decrypt_key(k,128,expkeyd);
        printchar((unsigned char*)key,16,"key");
        printchar(plain,lengthM,"plain");
        AES_encrypt(plain, cipher,expkey);
        AES_decrypt( cipher,plain,expkeyd);
        printchar(cipher,lengthM,"cipher");  
        printf("succes = %i\n",succes);
        printchar(decrypted,lengthM,"decrypt");
  return 0;
}


