#ifndef __DEFS_CONSTS_H
#define __DEFS_CONSTS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
  #define NULL ((void*)0)
#endif

#define TRUE  1
#define FALSE 0


/************************************************************************
 * Other constants
 ************************************************************************/

#define MASTER_BACKUP_KEY_SIZE 16

#define MODE_VIRGIN    0x00
#define MODE_ROOT      0x01
#define MODE_WORKING   0x02
#define MODE_LOCKED    0x03
#define MODE_DEAD      0x04

#define ACCESS_CODE_SIZE 8
#define PIN_SIZE 4
#define PUK_SIZE 8
#define MAC_SIZE 16
#define PASSWORD_SIZE 8
#define CHALLENGE_MAX_SIZE 224
#define SMALL_BUFFER_MAX_SIZE 32 // Must be >= 32
#define BUFFER_MAX_SIZE 512
#define RESURRECTION_KEY_SIZE 16
#define ID_SIZE 2
#define KEY_ID_SIZE 1
#define PROVER_ID_SIZE 1
#define SIZE_SIZE 2 // change this at your own risk

#ifdef TESTING_SC
  #define NUM_ISSUERS 3
  #define MAX_NUMBER_OF_BLOBS 10
  #define NUM_GROUPS ((NUM_ISSUERS)+1)
  #define NUM_COUNTERS (NUM_ISSUERS)
  #define NUM_AUTH_KEYS ((NUM_ISSUERS)+1)
  #define NUM_CREDS 20
  #define NUM_PROVERS 2
  #define NUM_GEN 3
#else
  #ifdef SODER
    #define NUM_ISSUERS 6
    #define MAX_NUMBER_OF_BLOBS 34 // was 40 in ALU 11, was 39
    #define NUM_GROUPS ((NUM_ISSUERS)+1)
    #define NUM_COUNTERS 0
    #define NUM_AUTH_KEYS 1
    #define NUM_CREDS 8
    #define NUM_PROVERS 1
    #define NUM_GEN 2
  #else
    #define NUM_ISSUERS 3
    #ifdef TEST_PATRAS_MODE
      #define MAX_NUMBER_OF_BLOBS 1
    #else
      #define MAX_NUMBER_OF_BLOBS 40
    #endif
    #define NUM_GROUPS ((NUM_ISSUERS)+1)
    #define NUM_COUNTERS (NUM_ISSUERS)
    #define NUM_AUTH_KEYS 2 //((NUM_ISSUERS)+1)
    #define NUM_CREDS 3
    #define NUM_PROVERS 1
    #define NUM_GEN 2
  #endif
#endif

#define GROUP_ID_SIZE 1
#define GEN_ID_SIZE 1
#define COUNTER_ID_SIZE 1
#define COMPTYPE_SIZE 1
#define CURSOR_SIZE 4
#define PROOFSESSION_SIZE 16
#define MAX_APDU_INPUT_DATA_SIZE BUFFER_MAX_SIZE // set to 512 bytes, could possibly be 1088-2*MAX_BIGINT_SIZE
#define MAX_APDU_OUTPUT_DATA_SIZE 255 // A multos card cannot output more than 255 data bytes. We use the GET RESPONSE trick to simulate long outputs.
#define MAX_URI_SIZE 64
#define MAX_BLOB_SIZE BUFFER_MAX_SIZE

#define MAX_PIN_TRIALS 3
#define MAX_PUK_TRIALS 3
#define MIN_X_SIZE 16
#define MAX_X_SIZE 32
#define MAX_SMALLINT_SIZE 128
#define MAX_BIGINT_SIZE   256 /* Must be equal to (BUFFER_MAX_SIZE / 2), otherwise singleOrDoubleExpo and crxModularMultiplication will not work correctly */
#define HASH_SIZE 32 // byte ouput size of SHA256


#ifdef __cplusplus
}
#endif

#endif // __DEFS_CONSTS_H
