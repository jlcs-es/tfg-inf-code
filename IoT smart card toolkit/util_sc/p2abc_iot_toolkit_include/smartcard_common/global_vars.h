#ifndef __GLOBAL_VARS_H
#define __GLOBAL_VARS_H

#include <smartcard_common/defs_types.h>
#include <smartcard_common/defs_consts.h>
#include <smartcard_common/APDU_types.h>
#include <smartcard_common/abc4T_types.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifdef TESTING_SC
extern BYTE test_device_key[32];
extern BYTE test_pin[4];
extern BYTE test_puk[8];
#endif

static char version[64]= "ABC4Trust Card Lite - Jose Luis Canovas 2016 - IoT Toolkit v1  "; // 64 bytes


/************************************************************************
 * Toolkit variables
 ************************************************************************/

extern SDWORD connfd;

/************************************************************************
 * Internal APDU variables.
 ************************************************************************/
extern BYTE ProtocolFlags;
extern BYTE ProtocolType;
extern BYTE GetResponseCLA;
extern BYTE GetResponseSW1;
extern BYTE CLA;
extern BYTE INS;
extern BYTE P1;
extern BYTE P2;
//extern BYTE P3;
//extern WORD P1P2;               /* P1 in MSB, P2 in LSB. */
extern WORD Lc;
extern WORD Le;
extern WORD La;
extern BYTE SW1;
extern BYTE SW2;
// extern WORD SW12;               /* SW1 in MSB, SW2 in LSB. */

extern BYTE APDU_Case;



/************************************************************************
 * Session data for the application (in RAM, but not public. Together
 * with the stack, limited to 960 bytes on ML2 cards)
 ************************************************************************/

extern WORD temp_size; // not used in subroutines

extern WORD challenge_size;

extern WORD pad_size;
extern BYTE authKeyId;
extern BYTE temp_group_id;
extern BYTE temp_gen_id;
extern BYTE temp_key_id;
extern BYTE temp_counter_id;
extern BYTE temp_issuer_id;
extern BYTE temp_prover_id;
extern BYTE temp_credential_id;
extern BYTE temp_gen_id_1;
extern BYTE temp_gen_id_2;
extern WORD temp_gen_1_size;
extern WORD temp_gen_2_size;
extern BYTE temp_status;
extern BYTE *temp_modulus;
extern WORD temp_modulus_size;
extern BYTE d;
extern WORD temp_blob_index;
extern WORD temp_blobcount;
extern WORD temp_uri_index;
extern BYTE temp_nread;
extern BYTE prev_nread;

extern WORD temp_buffer_size;
extern WORD temp_rand_size;

extern BYTE *uri;

extern WORD i, j;

extern BYTE device_id_prim[ID_SIZE];
extern WORD temp_key_size;

// the following variables are used in GET RESPONSE and allow to output more than 255 bytes
extern WORD remaining_size;
extern BYTE *remaining_position;

extern BYTE *buffer_ptr;

typedef union
{
    BYTE small_buffer[SMALL_BUFFER_MAX_SIZE];
    // BYTE pad[MAX_BIGINT_SIZE-32]; // FIX
    BYTE pad[MAX_BIGINT_SIZE];
    BYTE challenge[CHALLENGE_MAX_SIZE];
} MEM_SESSION;
extern MEM_SESSION mem_session;

/************************************************************************
 * Public data for the application (first data is placed at PB[0])
 ************************************************************************/

extern BYTE temp_buffer[2*MAX_BIGINT_SIZE]; // size max can be reached in the singleResponse subroutine, cannot be less than 512 bytes
extern APDU_DATA apdu_data;


/************************************************************************
 * Static data for the application
 ************************************************************************/

extern BLOB_STORE_ITEM   blob_store[MAX_NUMBER_OF_BLOBS]; // do not declare anything above 'blob_store': anything declared above blobs could be located in higher (not directly accessible) part of the e2 memory.
extern BLOB_CATALOG_ITEM blob_catalog[MAX_NUMBER_OF_BLOBS];
extern BYTE master_backup_key[MASTER_BACKUP_KEY_SIZE];
extern BYTE root_code[ACCESS_CODE_SIZE];
extern BYTE resurrection_key[RESURRECTION_KEY_SIZE];
extern BYTE pin_trials;
extern BYTE puk_trials;
extern BYTE device_id[ID_SIZE];
extern WORD x_size;
extern BYTE device_key[MAX_SMALLINT_SIZE];
extern BYTE puk[PUK_SIZE];
extern BYTE pin[PIN_SIZE];
extern BYTE mode;
extern BYTE auth_keys[NUM_AUTH_KEYS][MAX_BIGINT_SIZE];
extern WORD auth_keys_sizes[NUM_AUTH_KEYS]; // auth_keys_exist[key_id] > 0 iff the key exists, 0 otherwise
extern BYTE buffer[BUFFER_MAX_SIZE];
extern WORD buffer_size;
extern BYTE authData;
extern GROUP groups[NUM_GROUPS];
#if NUM_COUNTERS > 0
extern COUNTER counters[NUM_COUNTERS];
#endif
extern ISSUER issuers[NUM_ISSUERS];
extern PROVER provers[NUM_PROVERS];
extern BYTE current_prover_id;
extern CREDENTIAL credentials[NUM_CREDS];
extern BYTE temp_key[MAX_BIGINT_SIZE];

#ifdef __cplusplus
}
#endif

#endif //__GLOBAL_VARS_H
