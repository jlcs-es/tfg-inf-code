#ifndef __SHA_256_H
#define __SHA_256_H

#ifdef __cplusplus
extern "C" {
#endif

#include "smartcard_common/defs_types.h"


// SHA256

// MACROS
#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 byte digest

// DATA TYPES

//BYTE; 8-bit byte   //DWORD; 32-bit word
typedef struct {
    BYTE data[64];
    DWORD datalen;
    unsigned long long bitlen;
    DWORD state[8];
} SHA256_CTX;

// FUNCTION DECLARATIONS
void sha256_init(SHA256_CTX *ctx);
void sha256_update(SHA256_CTX *ctx, const BYTE data[], WORD len);
void sha256_final(SHA256_CTX *ctx, BYTE hash[]);

#ifdef __cplusplus
}
#endif

#endif //__SHA_256_H