/**
 * ADAPTED MULTOS CAPI
 * Multos' C API adapted to be used in our software smartcard.
 * Only the needed functions were implemented.
 * Every adapted function changes its name from multosFooBar() to mFooBar()
 */

#ifndef __M_ADAPTED_API_H
#define __M_ADAPTED_API_H

#include "defs_types.h"


#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************/
/********************** Multos Adapted C API ************************/
/********************************************************************/


/********************************************************************/
/** This a Multos C API adaptation, restricted to the functions     */
/* used in the P2ABC SW smartcards. The functions are the same      */
/* as in the CAPI documentation, changing 'multos' with 'm'.        */
/********************************************************************/
/** Provided implementation is written in pure C, only depending    */
/* on other provided files, so it can be platform independent.      */
/********************************************************************/

//

/**
 *  Documentation for this functions can be consulted in the Multos C API
 */

void mAESECBDecipher (BYTE *cipherText, BYTE *plainText, BYTE keyLength, BYTE *key);
void mAESECBEncipher (BYTE *plainText, BYTE *cipherText, BYTE keyLength, BYTE *key);
void mBlockAdd (const WORD blockLength, BYTE *block1, BYTE *block2, const BYTE *result);
void mBlockCopyFixedLength(BYTE blockLength, BYTE *blockSource, BYTE *blockDest);
void mBlockDecipherCBC (const BYTE algorithm, WORD inputLength, BYTE *cipherText, BYTE *plainText, BYTE initialValueLength, BYTE *initialValue, BYTE keyLength, BYTE *key);
void mBlockEncipherCBC (const BYTE algorithm, WORD inputLength, BYTE *plainText, BYTE *cipherText, BYTE initialValueLength, BYTE *initialValue, BYTE keyLength, BYTE *key);
void mBlockMultiply (const WORD blockLength, BYTE *block1, BYTE *block2, BYTE *result);
void mBlockSubtract (const WORD blockLength, BYTE *block1, BYTE *block2, const BYTE *result);
BOOL mCheckCase (BYTE isoCase);
void mExit (void);
void mExitLa (const BYTE la);
void mExitSW(const WORD sw);
void mExitSWLa (const WORD sw, const BYTE la);
void mGetRandomNumber(BYTE result[8]);
void mModularExponentiation (WORD exponentLength, WORD modulusLength, BYTE *exponent, BYTE *modulus, BYTE *input, BYTE *output);
void mModularMultiplication (WORD modulusLength, BYTE *modulus, BYTE *block1, BYTE *block2);
void mModularReduction (WORD operandLength, WORD modulusLength, BYTE *operand, BYTE *modulus);

/**
 * @brief Calculates SHA-256 digest of a message of arbitrary length.
 * The argument for \a hashLen must be 32, for SHA256. In the future other
 * values might be implemented.
 * @param msgLen Lenght of the message to digest
 * @param hashLen Only value supported is 32: SHA256
 * @param hashOut Buffer to save the digest
 * @param msgIn Message to digest
 */
void mSecureHash(WORD msgLen, WORD hashLen, BYTE *hashOut, BYTE *msgIn);

//

#ifdef __cplusplus
}
#endif

#endif //__M_ADAPTED_API_H