#ifndef __DEFS_ERRS_H
#define __DEFS_ERRS_H

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************
 * ERR Bytes Definitions
 ************************************************************************/

#define ERR_OK                                          0x9000
#define ERR_BAD_MODE                                    0x9A00 /* actually return 0x9Axx where xx is the current mode */
#define ERR_INCORRECT_MIN_SIZE_OF_INCOMMING_DATA        0x9B00 /* actually return 0x9Bxx where xx is the minimum expected size */
#define ERR_INCORRECT_SIZE_OF_INCOMMING_DATA            0x9C00 /* actually return 0x9Cxx where xx is the exact expected size */
#define ERR_INCORRECT_MIN_SIZE_OF_RAND                  0x9D00 /* actually return 0x9Dxx where xx is the minimum expected size of the random challenge */
#define ERR_INTEGER_EXCEEDS_MAXINTSIZE                  0x9F01
#define ERR_FAILED_ACCESS_PRIVILEGED_MODE               0x9F02
#define ERR_INCORRECT_PIN                               0x9F03
#define ERR_INCORRECT_PIN_AND_CARD_LOCKED               0x9F04
#define ERR_INCORRECT_PUK                               0x9F05
#define ERR_INCORRECT_PUK_AND_CARD_DEAD                 0x9F06
#define ERR_DEVICE_KEY_SHORTER_THAN_MIN_X_SIZE          0x9F07
#define ERR_KEY_ID_OUTSIDE_RANGE                        0x9F08
#define ERR_AUTHENTICATION_KEY_DOES_NOT_EXIST           0x9F09
#define ERR_DATA_AUTHENTICATED_WRT_NON_ROOT_KEY         0x9F0A
#define ERR_NEED_PRIOR_DATA_AUTHENTICATION_WRT_ROOT_KEY 0x9F0B
#define ERR_DATA_AUTHENTICATION_FAILURE                 0x9F0C
#define ERR_CMD_PARAMETERS_FAILED_ROOT_AUTHENTICATION   0x9F0D
#define ERR_AUTHENTICATION_KEY_TOO_SHORT                0x9F0E
#define ERR_GROUPID_OUTSIDE_OF_RANGE                    0x9F0F
#define ERR_GROUP_DOES_NOT_EXIST                        0x9F10
#define ERR_ID_OF_GROUP_GENERATOR_OUTSIDE_OF_RANGE      0x9F11
#define ERR_GENERATOR_DOES_NOT_EXIST                    0x9F12
#define ERR_COMPONENT_TYPE_OUTSIDE_OF_RANGE             0x9F13
#define ERR_COUNTER_ID_OUTSIDE_OF_RANGE                 0x9F14
#define ERR_COUNTER_DOES_NOT_EXIST                      0x9F15
#define ERR_ISSUERID_OUTSIDE_OF_RANGE                   0x9F16
#define ERR_ISSUER_DOES_NOT_EXIST                       0x9F17
#define ERR_PROVERID_OUTSIDE_OF_RANGE                   0x9F18
#define ERR_PROVER_DOES_NOT_EXIST                       0x9F19
#define ERR_ONE_ID_OF_CREDIDS_IS_OUTSIDE_OF_RANGE       0x9F1A
#define ERR_CREDENTIALID_OUTSIDE_OF_RANGE               0x9F1B
#define ERR_CREDENTIAL_DOES_NOT_EXIST                   0x9F1C
#define ERR_PROOF_SESSION_CANNOT_START                  0x9F1D
#define ERR_MALICIOUS_INPUT_RESPONSE_STAGE              0x9F1E
#define ERR_CURRENT_PROOF_SESSION_INAP_STAGE            0x9F1F
#define ERR_CREDENTIAL_INAP_STATE                       0x9F20
#define ERR_CREDENTIAL_OR_PSEUDO_NOT_MEMBER_PROOF_SESS  0x9F21
#define ERR_PRESENTATION_CRED_RESTRICTED_BY_IMM_COUNTER 0x9F22
#define ERR_URI_TOO_LARGE                               0x9F23
#define ERR_URI_CONTAINS_INVALID_CHARS                  0x9F24
#define ERR_NO_BLOB_WITH_GIVEN_URI                      0x9F25
#define ERR_BLOB_TOO_LARGE                              0x9F26
#define ERR_INVALID_BACKUP_ARCHIVE                      0x9F27
#define ERR_NO_CONTENT_TO_BACKUP                        0x9F28
#define ERR_MAX_NBR_BLOB_REACHED                        0x9F29
#define ERR_EXPONENT_LARGER_THAN_MODULUS                0x9F30 // if this changed, check the crxModularExponentiation routine in main.h

#define ERR_BAD_ISO     0x6700
#define ERR_BAD_CLA     0x6e00
#define ERR_BAD_INS     0x6d00

#define CRX_ERROR       0x9FFF



#ifdef __cplusplus
}
#endif

#endif // __DEFS_ERRS_H
