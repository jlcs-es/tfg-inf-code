#ifndef __CRYPTODEV_AES128_H
# define __CRYPTODEV_AES128_H

#ifdef __cplusplus
extern "C" {
#endif

#include <smartcard_external_utilities/cryptodev.h>


#define	AES_BLOCK_SIZE	16


int aes128cbc_ctx_init(struct cryptodev_ctx* ctx, int cfd, const unsigned char *key);
int aes128ecb_ctx_init(struct cryptodev_ctx* ctx, int cfd, const unsigned char *key);
void aes128_ctx_deinit(struct cryptodev_ctx* ctx);
int aes128_encrypt(struct cryptodev_ctx* ctx, const void* iv, const void* plaintext, void* ciphertext, size_t size);
int aes128_decrypt(struct cryptodev_ctx* ctx, const void* iv, const void* ciphertext, void* plaintext, size_t size);



#ifdef __cplusplus
}
#endif

#endif