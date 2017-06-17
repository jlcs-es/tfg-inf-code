#include <smartcard_utils_interface/crypto_util.h>



/* Implementation using /dev/crypto for HW acceleration */

#ifdef USE_CRYPTODEV

#include <smartcard_external_utilities/cryptodev-SHA256.h>
#include <smartcard_external_utilities/cryptodev-AES128.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>


int openDevCrypto(){
    /* Open the crypto device */
    int cfd = open("/dev/crypto", O_RDWR, 0);
    if (cfd < 0) {
        fprintf(stderr, "open(/dev/crypto)");
        return cfd;
    }
    /* Set close-on-exec (not really neede here) */
    if (fcntl(cfd, F_SETFD, 1) == -1) {
        fprintf(stderr, "fcntl(F_SETFD)");
        return -1;
    }
    return cfd;
}

void closeDevCrypto(int cfd){
    /* Close the original descriptor */
    if (close(cfd)) {
        perror("close(cfd)");
        return;
    }
}

void crypto_InitSeed(DWORD seed){

}

BYTE crypto_RandomByte(){
    return (BYTE)(1 % 256);
}


void crypto_SHA256(BYTE *digest, BYTE *message, WORD length) {
    struct cryptodev_ctx ctx;
    int cfd = openDevCrypto();
    if(cfd<0) return;

    sha256_ctx_init(&ctx, cfd, NULL, 0);
    sha256_hash(&ctx, message, length, digest);
    sha256_ctx_deinit(&ctx);

    closeDevCrypto(cfd);
}


void crypto_AES128_ECB_Encipher(BYTE *cipherText, BYTE *plainText, BYTE *key) {
    struct cryptodev_ctx ctx;
    int cfd = openDevCrypto();
    if(cfd < 0) return;

    aes128ecb_ctx_init(&ctx, cfd, key);
    aes128_encrypt(&ctx, NULL, plainText, cipherText, 16);
    aes128_ctx_deinit(&ctx);

    closeDevCrypto(cfd);
}


void crypto_AES128_ECB_Decipher(BYTE *plainText, BYTE *cipherText, BYTE *key) {

}


void crypto_AES128_CBC_Encipher (BYTE *cipherText, BYTE *plainText, WORD inputLength, BYTE *initialValue, BYTE *key){

}


void crypto_AES128_CBC_Decipher (BYTE *plainText, BYTE *cipherText, WORD inputLength, BYTE *initialValue, BYTE *key){

}



#else
#ifdef USE_OPENSSL
/* Implementation using openssl */

#include <openssl/sha.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

//void crypto_InitSeed(DWORD seed){
//    RAND_seed(&seed, 4);    // TODO check
//}
//
//BYTE crypto_RandomByte(){
//    BYTE b;
//    //RAND_bytes(&b, 1);    // FIXME
//    RAND_pseudo_bytes(&b, 1);
//    return b;
//}

#include <stdlib.h>

void crypto_InitSeed(DWORD seed){
    srand(seed);
}

BYTE crypto_RandomByte(){
    return (BYTE)(rand() % 256);
}



void crypto_SHA256(BYTE *digest, BYTE *message, WORD length) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, message, length);
    SHA256_Final(digest, &ctx);
}


void crypto_AES128_ECB_Encipher(BYTE *cipherText, BYTE *plainText, BYTE *key) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    AES_ecb_encrypt(plainText, cipherText, &enc_key, AES_ENCRYPT);
}


void crypto_AES128_ECB_Decipher(BYTE *plainText, BYTE *cipherText, BYTE *key) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    AES_ecb_encrypt(cipherText, plainText, &enc_key, AES_DECRYPT);
}


void crypto_AES128_CBC_Encipher (BYTE *cipherText, BYTE *plainText, WORD inputLength, BYTE *initialValue, BYTE *key){
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    AES_cbc_encrypt(plainText, cipherText, inputLength, &enc_key, initialValue, AES_ENCRYPT);
}


void crypto_AES128_CBC_Decipher (BYTE *plainText, BYTE *cipherText, WORD inputLength, BYTE *initialValue, BYTE *key){
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 128, &enc_key);
    AES_cbc_encrypt(cipherText, plainText, inputLength, &enc_key, initialValue, AES_DECRYPT);
}




#else

/* In this implementation we delegate on the adaptees tiny-AES128 and tiny-SHA256 */

// FIXME no pasan los tests!!

//#include <stdlib.h>
//#include <smartcard_external_utilities/tiny-AES128.h>
//#include <smartcard_external_utilities/tiny-SHA256.h>


void crypto_InitSeed(DWORD seed){
    srand(seed);
}

BYTE crypto_RandomByte(){
    return (BYTE)(rand() % 256);
}


void crypto_SHA256(BYTE *digest, BYTE *message, WORD length) {
//    SHA256_CTX ctx;
//    sha256_init(&ctx);
//    sha256_update(&ctx, message, length);
//    sha256_final(&ctx, digest);
}


void crypto_AES128_ECB_Encipher(BYTE *cipherText, BYTE *plainText, BYTE *key) {
    AES128_ECB_encrypt(plainText, key, cipherText);
}


void crypto_AES128_ECB_Decipher(BYTE *plainText, BYTE *cipherText, BYTE *key) {
    AES128_ECB_decrypt(cipherText, key, plainText);
}


void crypto_AES128_CBC_Encipher (BYTE *cipherText, BYTE *plainText, WORD inputLength, BYTE *initialValue, BYTE *key){
    AES128_CBC_encrypt_buffer(cipherText, plainText, inputLength, key, initialValue);
}


void crypto_AES128_CBC_Decipher (BYTE *plainText, BYTE *cipherText, WORD inputLength, BYTE *initialValue, BYTE *key){
    AES128_CBC_decrypt_buffer(plainText, cipherText, inputLength, key, initialValue);
}

#endif
#endif