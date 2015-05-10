#ifndef __SILC_AES_H
#define __SILC_AES_H

void SILC_AES128_ENC(const unsigned char* K,unsigned char* M,  unsigned long long mlen, unsigned char* C, unsigned char* N,  int nlen, unsigned char* A,  unsigned long long Alen, unsigned char* T);
int SILC_AES128_DEC(const unsigned char* K,unsigned char* M,  unsigned long long mlen, unsigned char* C, unsigned char* N,  int nlen, unsigned char* A,  unsigned long long Alen, unsigned char* T);

#endif


