#include <smartcard_utils_interface/arithmetic_util.h>


/********************************************************************/
/**********************Big Integer Arithmetic************************/
/********************************************************************/


#ifdef USE_GMP

/********************************************************************/
/*   Implementation of the adapter which delegates in miniGMP       */
/********************************************************************/

#include <gmp.h>

WORD getResultSizeInBytes(mpz_t op){
    WORD bytes = mpz_sizeinbase(op, 2) / 8;
    if(mpz_sizeinbase(op, 2) % 8){
        bytes++;
    }
    return bytes;
}


void addition(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length){
    mpz_t addend1, addend2, rop;
    mpz_init(addend1); mpz_init(addend2); mpz_init(rop);
    mpz_import(addend1, length, 1, sizeof(arr1[0]), 0, 0, arr1);
    mpz_import(addend2, length, 1, sizeof(arr2[0]), 0, 0, arr2);

    mpz_add(rop, addend1, addend2);


    WORD offset = length - getResultSizeInBytes(rop);
    for(WORD i=0; i<offset; ++i){
        result[i]=0;
    }
    mpz_export(result + offset, NULL, 1, sizeof(result[0]), 0, 0, rop);
}



void subtraction(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length){
    mpz_t minuend, subtrahend, rop;
    mpz_init(minuend); mpz_init(subtrahend); mpz_init(rop);
    mpz_import(minuend, length, 1, sizeof(arr1[0]), 0, 0, arr1);
    mpz_import(subtrahend, length, 1, sizeof(arr2[0]), 0, 0, arr2);

    mpz_sub(rop, minuend, subtrahend); // rop = minuend - subtrahend


    WORD offset = length - getResultSizeInBytes(rop);
    for(WORD i=0; i<offset; ++i){
        result[i]=0;
    }
    mpz_export(result + offset, NULL, 1, sizeof(result[0]), 0, 0, rop);
}


void multiplication(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length){
    mpz_t factor1, factor2, rop;
    mpz_init(factor1); mpz_init(factor2); mpz_init(rop);
    mpz_import(factor1, length, 1, sizeof(arr1[0]), 0, 0, arr1);
    mpz_import(factor2, length, 1, sizeof(arr2[0]), 0, 0, arr2);

    mpz_mul(rop, factor1, factor2);


    WORD offset = 2*length - getResultSizeInBytes(rop);
    for(WORD i=0; i<offset; ++i){
        result[i]=0;
    }
    mpz_export(result + offset, NULL, 1, sizeof(result[0]), 0, 0, rop);
}


void modularMultiplication(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length){
    mpz_t factor1, factor2, mod, rop;
    mpz_init(factor1); mpz_init(factor2); mpz_init(mod); mpz_init(rop);
    mpz_import(factor1, length, 1, sizeof(arr1[0]), 0, 0, arr1);
    mpz_import(factor2, length, 1, sizeof(arr2[0]), 0, 0, arr2);
    mpz_import(mod, length, 1, sizeof(modulus[0]), 0, 0, modulus);

    mpz_mod(factor1, factor1, mod);
    mpz_mod(factor2, factor2, mod);
    mpz_mul(rop, factor1, factor2);
    mpz_mod(rop, rop, mod);


    WORD offset = length - getResultSizeInBytes(rop);
    for(WORD i=0; i<offset; ++i){
        result[i]=0;
    }
    mpz_export(result + offset, NULL, 1, sizeof(result[0]), 0, 0, rop);

}


void modularExponentiation(BYTE *result, BYTE *base, BYTE *exponent, BYTE *modulus, WORD modulusLength, WORD exponentLength){
    mpz_t b, exp, mod, rop;
    mpz_init(b); mpz_init(exp); mpz_init(mod); mpz_init(rop);
    mpz_import(b, modulusLength, 1, sizeof(base[0]), 0, 0, base);
    mpz_import(exp, exponentLength, 1, sizeof(exponent[0]), 0, 0, exponent);
    mpz_import(mod, modulusLength, 1, sizeof(modulus[0]), 0, 0, modulus);

    mpz_powm(rop, b, exp, mod);


    WORD offset = modulusLength - getResultSizeInBytes(rop);
    for(WORD i=0; i<offset; ++i){
        result[i]=0;
    }
    mpz_export(result + offset, NULL, 1, sizeof(result[0]), 0, 0, rop);

}


void modularReduction(BYTE *result, BYTE *operand, BYTE *modulus, WORD operandLength, WORD modulusLength){
    mpz_t rop, base, mod;
    mpz_init(rop); mpz_init(base); mpz_init(mod);
    mpz_import(base, operandLength, 1, sizeof(operand[0]), 0, 0, operand);
    mpz_import(mod, modulusLength, 1, sizeof(modulus[0]), 0, 0, modulus);


    mpz_mod(rop, base, mod);

    WORD offset = modulusLength - getResultSizeInBytes(rop);
    for(WORD i=0; i<offset; ++i){
        result[i]=0;
    }
    mpz_export(result + offset, NULL, 1, sizeof(result[0]), 0, 0, rop);

    // TODO: test

}





#else // Default use sw generic provided implementation:
// FIXME : if these functions can't overlap result, create the intermediate array
/********************************************************************/
/*   Implementation of the facade that delegates in SW BYTE arrays  */
/* operations.                                                      */
/********************************************************************/
/*
#include <arithmetic_implementation_v1.h>


void multiplication(BYTE *result, BYTE *arr1, BYTE *arr2, WORD length){
    product(result, arr1, arr2, length);
}


void modularMultiplication(BYTE *result, BYTE *arr1, BYTE *arr2, BYTE *modulus, WORD length){
    modular_product(result, arr1, arr2, modulus, length);
}


void modularExponentiation(BYTE *result, BYTE *base, BYTE *exponent, BYTE *modulus, WORD modulusLength, WORD exponentLength){
    modular_exponentiation(result, base, exponent, modulus, modulusLength, exponentLength);
}


void modularReduction(BYTE *result, BYTE *operand, BYTE *modulus, WORD operandLength, WORD modulusLength){
    // TODO
}
*/
#endif