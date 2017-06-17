#ifndef __APDU_TYPES_H
#define __APDU_TYPES_H

#include "defs_types.h"
#include "defs_consts.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 * APDU structures
 ************************************************************************/

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE keyId;
} APDU_READ_AUTHENTICATION_KEY;

typedef struct __attribute__((__packed__))
{
  BYTE group_id;
  BYTE comptype;
} APDU_SET_GROUP_COMPONENT;

typedef struct __attribute__((__packed__))
{
  BYTE group_id;
  BYTE genId;
} APDU_SET_GENERATOR;

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE group_id;
} APDU_READ_GROUP_IN;

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE group_id;
  BYTE comptype;
} APDU_READ_GROUP_COMPONENT_IN;

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE group_id;
  BYTE gen_id;
} APDU_READ_GENERATOR_IN;

typedef struct __attribute__((__packed__))
{
  BYTE counter_id;
  BYTE key_id;
  BYTE index;
  BYTE threshold;
  BYTE cursor[CURSOR_SIZE];
} APDU_SET_COUNTER;

typedef struct __attribute__((__packed__))
{
  BYTE key_id;
  BYTE sig[MAX_BIGINT_SIZE];
} APDU_INCREMENT_COUNTER;

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE counter_id;
} APDU_READ_COUNTER_IN;

typedef struct __attribute__((__packed__))
{
  BYTE issuer_id;
  BYTE group_id;
  BYTE gen_id_1;
  BYTE gen_id_2;
  BYTE numpres;
  BYTE counter_id;
} APDU_SET_ISSUER_IN;

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE issuer_id;
} APDU_READ_ISSUER_IN;

typedef struct __attribute__((__packed__))
{
  BYTE prover_id;
  WORD ksize;
  WORD csize;
  BYTE cred_ids[NUM_CREDS];
} APDU_SET_PROVER_IN;

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE prover_id;
} APDU_READ_PROVER_IN;

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE prover_id;
} APDU_START_COMMITMENTS_IN;

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE prover_id;
  BYTE input[MAX_APDU_INPUT_DATA_SIZE-PIN_SIZE-1];
} APDU_START_RESPONSES_IN;

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE credential_id;
  BYTE issuer_id;
} APDU_SET_CREDENTIAL_IN;

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE credential_id;
} APDU_PIN_AND_CREDENTIAL_ID;

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE scope[MAX_APDU_INPUT_DATA_SIZE-PIN_SIZE];
} APDU_GET_SCOPE_EXCLUSIVE_PSEUDONYM_IN;

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE scope[MAX_APDU_INPUT_DATA_SIZE-PIN_SIZE];
} APDU_GET_SCOPE_EXCLUSIVE_COMMITMENT_IN;

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE scope[MAX_APDU_INPUT_DATA_SIZE-PIN_SIZE];
} APDU_GET_SCOPE_EXCLUSIVE_RESPONSE_IN;

typedef struct __attribute__((__packed__))
{
  BYTE datain[PIN_SIZE+MAX_URI_SIZE];
} APDU_BLOB_IN;

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE nread;
} APDU_LIST_BLOBS_IN;

typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE password[PASSWORD_SIZE];
} APDU_BACKUP_IN;

#ifdef SODER
typedef struct __attribute__((__packed__))
{
  BYTE pin[PIN_SIZE];
  BYTE password[PASSWORD_SIZE];
  BYTE credential_id;
} APDU_BACKUP_CREDENTIAL_IN;
#endif


typedef union
{
    // structures and variables used for output
    BYTE mode;
    BYTE pin_trials;
    BYTE puk_trials;
    BYTE challenge[CHALLENGE_MAX_SIZE];
    BYTE device_id[ID_SIZE];
    BYTE version[64];
    BYTE memspace[2];
    BYTE dataout[MAX_APDU_OUTPUT_DATA_SIZE];
    BYTE access_code[ACCESS_CODE_SIZE];
    BYTE mac[MAC_SIZE];
    APDU_READ_AUTHENTICATION_KEY read_authentication_key;
    APDU_SET_GROUP_COMPONENT set_group_component;
    APDU_SET_GENERATOR set_generator;
    BYTE proofsession[PROOFSESSION_SIZE];
    // structures and variables used for input
    BYTE challenge_size;
    BYTE old_pin_and_new_pin[PIN_SIZE << 1];
    BYTE puk_and_pin[PUK_SIZE + PIN_SIZE];
    BYTE id_and_size[ID_SIZE + SIZE_SIZE];
    BYTE small_buffer[SMALL_BUFFER_MAX_SIZE];
    BYTE pin[PIN_SIZE];
    BYTE buffer[BUFFER_MAX_SIZE];
    BYTE keyId;
    BYTE auth_key[MAX_BIGINT_SIZE];
    APDU_READ_GROUP_IN read_group_in;
    APDU_READ_GROUP_COMPONENT_IN read_group_component_in;
    APDU_READ_GENERATOR_IN read_generator_in;
    BYTE group_id;
    APDU_SET_COUNTER set_counter;
    APDU_INCREMENT_COUNTER increment_counter;
    APDU_READ_COUNTER_IN read_counter_in;
    BYTE counter_id;
    APDU_SET_ISSUER_IN set_issuer_in;
    APDU_READ_ISSUER_IN read_issuer_in;
    BYTE issuer_id;
    APDU_SET_PROVER_IN set_prover_in;
    APDU_READ_PROVER_IN read_prover_in;
    BYTE prover_id;
    APDU_START_COMMITMENTS_IN start_commitments_in;
    APDU_START_RESPONSES_IN start_responses_in;
    APDU_SET_CREDENTIAL_IN set_credential_in;
    APDU_PIN_AND_CREDENTIAL_ID pin_and_credential_id;
    APDU_GET_SCOPE_EXCLUSIVE_PSEUDONYM_IN get_scope_exclusive_pseudonym_in;
    APDU_GET_SCOPE_EXCLUSIVE_COMMITMENT_IN get_scope_exclusive_commitment_in;
    APDU_GET_SCOPE_EXCLUSIVE_RESPONSE_IN get_scope_exclusive_response_in;
    APDU_BLOB_IN blob_in;
    APDU_LIST_BLOBS_IN list_blobs_in;
    APDU_BACKUP_IN backup_in;
#ifdef SODER
    APDU_BACKUP_CREDENTIAL_IN backup_credential_in;
#endif
} APDU_DATA;



#ifdef __cplusplus
}
#endif

#endif // __APDU_TYPES_H
