#ifndef __APDU_HANDLER_H
#define __APDU_HANDLER_H

#include "defs_types.h"

#ifdef __cplusplus
extern "C" {
#endif


void handle_APDU(BYTE *apdu_bytes, int length);

#ifdef TEST_PATRAS_MODE       //TODO: remove if not necessary
void handle_INS_GET_KX_AND_DEVICE_KEY(void);
void handle_INS_TEST(void);
#endif
void handle_INS_GET_MODE(void);
void handle_INS_SET_ROOT_MODE(void);
void handle_INS_SET_WORKING_MODE(void);
void handle_INS_SET_VIRGIN_MODE(void);
void handle_INS_SET_FAST_VIRGIN_MODE(void);
void handle_INS_PIN_TRIALS_LEFT(void);
void handle_INS_PUK_TRIALS_LEFT(void);
void handle_INS_CHANGE_PIN(void);
void handle_INS_RESET_PIN(void);
void handle_INS_INITIALIZE_DEVICE(void);
void handle_INS_GET_DEVICE_ID(void);
void handle_INS_GET_VERSION(void);
void handle_INS_PUT_DATA(void);
void handle_INS_GET_CHALLENGE(void);
void handle_INS_AUTHENTICATE_DATA(void);
void handle_INS_SET_AUTHENTICATION_KEY(void);
void handle_INS_LIST_AUTHENTICATION_KEYS(void);
void handle_INS_READ_AUTHENTICATION_KEY(void);
void handle_INS_REMOVE_AUTHENTICATION_KEY(void);
void handle_INS_SET_GROUP_COMPONENT(void);
void handle_INS_SET_GENERATOR(void);
void handle_INS_LIST_GROUPS(void);
void handle_INS_READ_GROUP(void);
void handle_INS_READ_GROUP_COMPONENT(void);
void handle_INS_READ_GENERATOR(void);
void handle_INS_REMOVE_GROUP(void);
void handle_INS_SET_COUNTER(void);
void handle_INS_INCREMENT_COUNTER(void);
void handle_INS_LIST_COUNTERS(void);
void handle_INS_READ_COUNTER(void);
void handle_INS_REMOVE_COUNTER(void);
void handle_INS_SET_ISSUER(void);
void handle_INS_LIST_ISSUERS(void);
void handle_INS_READ_ISSUER(void);
void handle_INS_REMOVE_ISSUER(void);
void handle_INS_SET_PROVER(void);
void handle_INS_READ_PROVER(void);
void handle_INS_REMOVE_PROVER(void);
void handle_INS_START_COMMITMENTS(void);
void handle_INS_START_RESPONSES(void);
void handle_INS_SET_CREDENTIAL(void);
void handle_INS_LIST_CREDENTIALS(void);
void handle_INS_READ_CREDENTIAL(void);
void handle_INS_REMOVE_CREDENTIAL(void);
void handle_INS_GET_CREDENTIAL_PUBLIC_KEY(void);
void handle_INS_GET_ISSUANCE_COMMITMENT(void);
void handle_INS_GET_ISSUANCE_RESPONSE(void);
void handle_INS_GET_PRESENTATION_COMMITMENT(void);
void handle_INS_GET_PRESENTATION_RESPONSE(void);
void handle_INS_GET_DEVICE_PUBLIC_KEY(void);
void handle_INS_GET_DEVICE_COMMITMENT(void);
void handle_INS_GET_DEVICE_RESPONSE(void);
void handle_INS_GET_SCOPE_EXCLUSIVE_PSEUDONYM(void);
void handle_INS_GET_SCOPE_EXCLUSIVE_COMMITMENT(void);
void handle_INS_GET_SCOPE_EXCLUSIVE_RESPONSE(void);
void handle_INS_STORE_BLOB(void);
void handle_INS_LIST_BLOBS(void);
void handle_INS_READ_BLOB(void);
void handle_INS_REMOVE_BLOB(void);
void handle_INS_BACKUP_DEVICE(void);
void handle_INS_RESTORE_DEVICE(void);
void handle_INS_BACKUP_COUNTERS(void);
void handle_INS_RESTORE_COUNTERS(void);
#ifdef SODER    //TODO: remove if not necessary
void handle_INS_BACKUP_CREDENTIAL(void);
void handle_INS_RESTORE_CREDENTIAL(void);
#endif
void handle_INS_GET_INFO(void);
void handle_INS_NOTHING(void);
void handle_INS_GET_RESPONSE(void);


#ifdef __cplusplus
}
#endif

#endif // __APDU_HANDLER_H
