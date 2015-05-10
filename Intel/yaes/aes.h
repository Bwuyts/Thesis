#ifndef __AES_H
#define __AES_H

inline void AES_128_Key_Expansion (const __m128i userkey, __m128i* Key_Schedule);
inline __m128i AES_ECB_encrypt(const __m128i in,const __m128i *key);
inline void AES_ECB_decrypt(const __m128i *in, __m128i *out, unsigned long length, const __m128i *key, int number_of_rounds);


#endif


