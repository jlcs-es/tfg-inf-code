/*
 * Demo on how to use /dev/crypto device for ciphering.
 *
 * Placed under public domain.
 *
 */
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <smartcard_external_utilities/cryptodev.h>
#include <smartcard_external_utilities/cryptodev-SHA256.h>

int sha256_ctx_init(struct cryptodev_ctx* ctx, int cfd, const unsigned char *key, unsigned int key_size)
{
#ifdef CIOCGSESSINFO
    struct session_info_op siop;
#endif

    memset(ctx, 0, sizeof(*ctx));
    ctx->cfd = cfd;

    if (key == NULL)
        ctx->sess.mac = CRYPTO_SHA2_256;
    else {
        ctx->sess.mac = CRYPTO_SHA2_256_HMAC;
        ctx->sess.mackeylen = key_size;
        ctx->sess.mackey = (void*)key;
    }
    if (ioctl(ctx->cfd, CIOCGSESSION, &ctx->sess)) {
        perror("ioctl(CIOCGSESSION)");
        return -1;
    }

#ifdef CIOCGSESSINFO
    siop.ses = ctx->sess.ses;
	if (ioctl(ctx->cfd, CIOCGSESSINFO, &siop)) {
		perror("ioctl(CIOCGSESSINFO)");
		return -1;
	}
	fprintf(stderr, "Got %s with driver %s\n",
			siop.hash_info.cra_name, siop.hash_info.cra_driver_name);
	if (!(siop.flags & SIOP_FLAG_KERNEL_DRIVER_ONLY)) {
		fprintf(stderr, "Note: This is not an accelerated cipher\n");
	}
	/*fprintf(stderr, "Alignmask is %x\n", (unsigned int)siop.alignmask);*/
	ctx->alignmask = siop.alignmask;
#endif
    return 0;
}

void sha256_ctx_deinit(struct cryptodev_ctx* ctx)
{
    if (ioctl(ctx->cfd, CIOCFSESSION, &ctx->sess.ses)) {
        perror("ioctl(CIOCFSESSION)");
    }
}

int sha256_hash(struct cryptodev_ctx* ctx, const void* text, unsigned int size, void* digest)
{
    struct crypt_op cryp;
    void* p;

    /* check text and ciphertext alignment */
    if (ctx->alignmask) {
        p = (void*)(((unsigned long)text + ctx->alignmask) & ~ctx->alignmask);
        if (text != p) {
            fprintf(stderr, "text is not aligned\n");
            return -1;
        }
    }

    memset(&cryp, 0, sizeof(cryp));

    /* Encrypt data.in to data.encrypted */
    cryp.ses = ctx->sess.ses;
    cryp.len = size;
    cryp.src = (void*)text;
    cryp.mac = digest;
    if (ioctl(ctx->cfd, CIOCCRYPT, &cryp)) {
        perror("ioctl(CIOCCRYPT)");
        return -1;
    }

    return 0;
}
