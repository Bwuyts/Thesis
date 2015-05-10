#ifndef __AES_H
#define __AES_H

void AES_COPA_encrypt(unsigned char* M,int mlen,const unsigned char* A, int Alen, const unsigned char* N, int Nlen, unsigned char*C,  unsigned char* T , const unsigned char* K);
int AES_COPA_decrypt( unsigned char* C,int clen, const unsigned char * A, int Alen, const unsigned char* N, int Nlen,unsigned char*M,unsigned char* T , const unsigned char* K);

#endif



