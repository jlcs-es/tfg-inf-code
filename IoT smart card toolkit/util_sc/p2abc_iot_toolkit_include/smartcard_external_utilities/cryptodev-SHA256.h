#ifndef __CRYPTODEV_SHA256_H
#define __CRYPTODEV_SHA256_H

#ifdef __cplusplus
extern "C" {
#endif


#include <smartcard_external_utilities/cryptodev.h>



int sha256_ctx_init(struct cryptodev_ctx* ctx, int cfd, const unsigned char *key, unsigned int key_size);
void sha256_ctx_deinit(struct cryptodev_ctx* ctx);
int sha256_hash(struct cryptodev_ctx* ctx, const void* text, unsigned int size, void* digest);


#ifdef __cplusplus
}
#endif


#endif