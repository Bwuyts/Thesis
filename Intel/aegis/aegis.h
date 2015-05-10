#ifndef __AEGIS_H
#define __AEGIS_H
inline void encrypt(const unsigned char* key, unsigned char* IV,unsigned char* Adata, unsigned char* plain, unsigned char* cipher, unsigned char* tag,int64_t adlen,int64_t msglen);
inline int decrypt(const unsigned char* key, unsigned char* IV,unsigned char* Adata, unsigned char* cipher, unsigned char* plain, unsigned char* tag, int64_t adlen,int64_t msglen);
#endif
