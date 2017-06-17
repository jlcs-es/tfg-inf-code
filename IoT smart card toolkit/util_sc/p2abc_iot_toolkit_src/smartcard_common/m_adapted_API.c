#include <smartcard_common/m_adapted_API.h>
#include <smartcard_common/defs_errs.h>
#include <smartcard_utils_interface/system_funcs.h>
#include <smartcard_utils_interface/crypto_util.h>
#include <smartcard_utils_interface/arithmetic_util.h>
#include <smartcard_common/global_vars.h>
#include <smartcard_utils_interface/APDU_IO_util.h>
#include <smartcard_utils_interface/serialize_util.h>


void mAESECBDecipher (BYTE *cipherText, BYTE *plainText, BYTE keyLength, BYTE *key){
    if(keyLength != 16) // Only implemented AES128
        return; // TODO: avisar de error de implementación
    crypto_AES128_ECB_Decipher(plainText, cipherText, key);
}

void mAESECBEncipher (BYTE *plainText, BYTE *cipherText, BYTE keyLength, BYTE *key){
    if(keyLength != 16) // Only implemented AES128
        return; // TODO: avisar de error de implementación
    crypto_AES128_ECB_Encipher(cipherText, plainText, key);
    // BYTE *plaintext: address of 16 bytes of plaintext (input) -> tiny-AES128 hace los ECB en bloques de 16bytes  -> OK
}


void mBlockAdd (const WORD blockLength, BYTE *block1, BYTE *block2, const BYTE *result){
    addition(result, block1, block2, blockLength);
}


void mBlockCopyFixedLength(BYTE blockLength, BYTE *blockSource, BYTE *blockDest){
    mem_move(blockDest, blockSource, blockLength);
}


void mBlockDecipherCBC (const BYTE algorithm, WORD inputLength, BYTE *cipherText, BYTE *plainText,
                              BYTE initialValueLength, BYTE *initialValue, BYTE keyLength, BYTE *key){

    //   AlgorithmID : 0x06  AES
    if(algorithm != 0x06)
        return;
    //  Key Length : 16bytes=128bits AES128
    if(keyLength != 16)
        return;
    //  Initial Value Length : 16 bytes AES
    if(initialValueLength != 16)
        return;

    crypto_AES128_CBC_Decipher (plainText, cipherText, inputLength, initialValue, key);

}


void mBlockEncipherCBC (const BYTE algorithm, WORD inputLength, BYTE *plainText, BYTE *cipherText,
                              BYTE initialValueLength, BYTE *initialValue, BYTE keyLength, BYTE *key){

    //   AlgorithmID : 0x06  AES
    if(algorithm != 0x06)
        return;
    //  Key Length : 16bytes=128bits AES128
    if(keyLength != 16)
        return;
    //  Initial Value Length : 16 bytes AES
    if(initialValueLength != 16)
        return;

    crypto_AES128_CBC_Encipher (cipherText, plainText, inputLength, initialValue, key);
}


void mBlockMultiply (const WORD blockLength, BYTE *block1, BYTE *block2, BYTE *result){
    multiplication(result, block1, block2, blockLength);
}



void mBlockSubtract (const WORD blockLength, BYTE *block1, BYTE *block2, const BYTE *result){
    subtraction(result, block2, block1, blockLength);
    //    NOTE: result = block2 - block1
    //    This function subtracts the value found in block1 to that found in block2 and places the difference
    //    in the block indicated in result.
}

BOOL mCheckCase (BYTE isoCase){
    return isoCase == APDU_Case;
}

void mExit (void){
    save_status();
    output_apdu_response();
}


void mExitLa (const BYTE la){
    La = la;
    mExit();
}
void mExitSW(const WORD sw){
    SW1 = (BYTE) ( ( sw >> 8) & 0xff ) ;
    SW2 = (BYTE) ( sw & 0xff );
    mExit();
}
void mExitSWLa (const WORD sw, const BYTE la){
    SW1 = (BYTE) ( ( sw >> 8) & 0xff ) ;
    SW2 = (BYTE) ( sw & 0xff );
    La = la;
    mExit();
}


void mGetRandomNumber(BYTE result[8]){
    int i;
    for (i = 0; i < 8; i++) {
        result[i] = crypto_RandomByte() % 256;
    }
}



void mModularExponentiation (WORD exponentLength, WORD modulusLength, BYTE *exponent, BYTE *modulus, BYTE *input, BYTE *output) {
    if (exponentLength > modulusLength)
        mExitSW(ERR_EXPONENT_LARGER_THAN_MODULUS); // From crxModularExponentiation original implementation
    modularExponentiation(output, input, exponent, modulus, modulusLength, exponentLength);
}



void mModularMultiplication (WORD modulusLength, BYTE *modulus, BYTE *block1, BYTE *block2){
    modularMultiplication(block1, block1, block2, modulus, modulusLength);
}


void mModularReduction (WORD operandLength, WORD modulusLength, BYTE *operand, BYTE *modulus){
    modularReduction(operand, operand, modulus, operandLength, modulusLength);
}


void mSecureHash(WORD msgLen, WORD hashLen, BYTE *hashOut, BYTE *msgIn) {
    if(hashLen != 32)
        return; // TODO: avisar de error de implementación
    crypto_SHA256(hashOut, msgIn, msgLen);
}


