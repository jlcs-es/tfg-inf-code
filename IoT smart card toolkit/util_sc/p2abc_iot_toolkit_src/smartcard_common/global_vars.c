#include <smartcard_common/global_vars.h>

#ifdef TESTING_SC
BYTE test_device_key[32] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
BYTE test_pin[4] = {0x31, 0x32, 0x33, 0x34};
BYTE test_puk[8] = {0x31, 0x32, 0x33, 0x34, 0x31, 0x32, 0x33, 0x34};
#endif

/************************************************************************
 * Toolkit variables
 ************************************************************************/

SDWORD connfd;

/************************************************************************
 * Internal APDU variables.
 ************************************************************************/
BYTE ProtocolFlags;
BYTE ProtocolType;
BYTE GetResponseCLA;
BYTE GetResponseSW1;
BYTE CLA;
BYTE INS;
BYTE P1;
BYTE P2;
//BYTE P3;
//WORD P1P2;               /* P1 in MSB, P2 in LSB. */
WORD Lc;
WORD Le;
WORD La;
BYTE SW1;
BYTE SW2;
// WORD SW12;               /* SW1 in MSB, SW2 in LSB. */

BYTE APDU_Case;

/************************************************************************
 * Session data for the application (in RAM, but not public. Together
 * with the stack, limited to 960 bytes on ML2 cards)
 ************************************************************************/

WORD temp_size; // not used in subroutines
WORD challenge_size = 0;
WORD pad_size;
BYTE authKeyId;
BYTE temp_group_id;
BYTE temp_gen_id;
BYTE temp_key_id;
BYTE temp_counter_id;
BYTE temp_issuer_id;
BYTE temp_prover_id;
BYTE temp_credential_id;
BYTE temp_gen_id_1;
BYTE temp_gen_id_2;
WORD temp_gen_1_size;
WORD temp_gen_2_size;
BYTE temp_status;
BYTE *temp_modulus;
WORD temp_modulus_size;
BYTE d;
WORD temp_blob_index;
WORD temp_blobcount;
WORD temp_uri_index;
BYTE temp_nread;
BYTE prev_nread;
WORD temp_buffer_size;
WORD temp_rand_size;
BYTE *uri;
WORD i, j;
BYTE device_id_prim[ID_SIZE];
WORD temp_key_size;

// the following variables are used in GET RESPONSE and allow to output more than 255 bytes
WORD remaining_size;
BYTE *remaining_position;

BYTE *buffer_ptr;

MEM_SESSION mem_session;



/************************************************************************
 * Public data for the application (first data is placed at PB[0])
 ************************************************************************/

BYTE temp_buffer[2*MAX_BIGINT_SIZE]; // size max can be reached in the singleResponse subroutine, cannot be less than 512 bytes

APDU_DATA apdu_data;

/************************************************************************
 * Static data for the application
 ************************************************************************/

BLOB_STORE_ITEM   blob_store[MAX_NUMBER_OF_BLOBS];
BLOB_CATALOG_ITEM blob_catalog[MAX_NUMBER_OF_BLOBS];
BYTE master_backup_key[MASTER_BACKUP_KEY_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
BYTE root_code[ACCESS_CODE_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
BYTE resurrection_key[RESURRECTION_KEY_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
BYTE pin_trials = MAX_PIN_TRIALS;
BYTE puk_trials = MAX_PUK_TRIALS;
BYTE device_id[ID_SIZE];
WORD x_size;
BYTE device_key[MAX_SMALLINT_SIZE];
BYTE puk[PUK_SIZE];
BYTE pin[PIN_SIZE];
BYTE mode = MODE_VIRGIN;
BYTE auth_keys[NUM_AUTH_KEYS][MAX_BIGINT_SIZE];
WORD auth_keys_sizes[NUM_AUTH_KEYS]; // auth_keys_exist[key_id] > 0 iff the key exists, 0 otherwise
BYTE buffer[BUFFER_MAX_SIZE];
WORD buffer_size = 0;
BYTE authData = 0;
GROUP groups[NUM_GROUPS];
#if NUM_COUNTERS > 0
COUNTER counters[NUM_COUNTERS];
#endif
ISSUER issuers[NUM_ISSUERS];
PROVER provers[NUM_PROVERS];
BYTE current_prover_id;
CREDENTIAL credentials[NUM_CREDS];
BYTE temp_key[MAX_BIGINT_SIZE];

