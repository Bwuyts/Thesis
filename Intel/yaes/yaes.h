#ifndef __YAES_H
#define __YAES_H

void YAES128_ENC(unsigned char* roundkey,const unsigned char *N, const unsigned char *A, unsigned char *M, unsigned char *C, unsigned char *T, int Tau, int lengthM, int lengthA, int lengthN);
int YAES128_DEC(const unsigned char* K,const unsigned char *N,const unsigned char *A, unsigned char *M, unsigned char *C, unsigned char *T, int Tau, int lengthM, int lengthA, int lengthN);
void initialise(unsigned char* roundkeys , const unsigned char* K);

#endif


