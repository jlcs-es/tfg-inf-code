#ifndef __DEFS_INS_H
#define __DEFS_INS_H


#ifdef __cplusplus
extern "C" {
#endif



#define ABC_CLA 0xBC

/************************************************************************
 * INS Bytes Definitions
 ************************************************************************/

#ifdef TEST_PATRAS_MODE       //TODO: remove if not necessary
#define INS_GET_KX_AND_DEVICE_KEY          0x00
#define INS_TEST                           0x01
#endif
#define INS_GET_MODE                       0x02
#define INS_SET_ROOT_MODE                  0x04
#define INS_SET_WORKING_MODE               0x06
#define INS_SET_VIRGIN_MODE                0x08
#define INS_SET_FAST_VIRGIN_MODE           0x09
#define INS_PIN_TRIALS_LEFT                0x0A
#define INS_PUK_TRIALS_LEFT                0x0C
#define INS_CHANGE_PIN                     0x0E
#define INS_RESET_PIN                      0x10
#define INS_INITIALIZE_DEVICE              0x12
#define INS_GET_DEVICE_ID                  0x14
#define INS_GET_VERSION                    0x16
#define INS_PUT_DATA                       0x1A
#define INS_GET_CHALLENGE                  0x1C
#define INS_AUTHENTICATE_DATA              0x1E
#define INS_SET_AUTHENTICATION_KEY         0x20
#define INS_LIST_AUTHENTICATION_KEYS       0x22
#define INS_READ_AUTHENTICATION_KEY        0x24
#define INS_REMOVE_AUTHENTICATION_KEY      0x26
#define INS_SET_GROUP_COMPONENT            0x28
#define INS_SET_GENERATOR                  0x2A
#define INS_LIST_GROUPS                    0x2C
#define INS_READ_GROUP                     0x2E
#define INS_READ_GROUP_COMPONENT           0x30
#define INS_READ_GENERATOR                 0x32
#define INS_REMOVE_GROUP                   0x34
#define INS_SET_COUNTER                    0x36
#define INS_INCREMENT_COUNTER              0x38
#define INS_LIST_COUNTERS                  0x3A
#define INS_READ_COUNTER                   0x3C
#define INS_REMOVE_COUNTER                 0x3E
#define INS_SET_ISSUER                     0x40
#define INS_LIST_ISSUERS                   0x42
#define INS_READ_ISSUER                    0x44
#define INS_REMOVE_ISSUER                  0x46
#define INS_SET_PROVER                     0x48
#define INS_READ_PROVER                    0x4A
#define INS_REMOVE_PROVER                  0x4C
#define INS_START_COMMITMENTS              0x4E
#define INS_START_RESPONSES                0x50
#define INS_SET_CREDENTIAL                 0x52
#define INS_LIST_CREDENTIALS               0x54
#define INS_READ_CREDENTIAL                0x56
#define INS_REMOVE_CREDENTIAL              0x58
#define INS_GET_CREDENTIAL_PUBLIC_KEY      0x5A
#define INS_GET_ISSUANCE_COMMITMENT        0x5C
#define INS_GET_ISSUANCE_RESPONSE          0x5E
#define INS_GET_PRESENTATION_COMMITMENT    0x60
#define INS_GET_PRESENTATION_RESPONSE      0x62
#define INS_GET_DEVICE_PUBLIC_KEY          0x64
#define INS_GET_DEVICE_COMMITMENT          0x66
#define INS_GET_DEVICE_RESPONSE            0x68
#define INS_GET_SCOPE_EXCLUSIVE_PSEUDONYM  0x6A
#define INS_GET_SCOPE_EXCLUSIVE_COMMITMENT 0x6C
#define INS_GET_SCOPE_EXCLUSIVE_RESPONSE   0x6E
#define INS_STORE_BLOB                     0x70
#define INS_LIST_BLOBS                     0x72
#define INS_READ_BLOB                      0x74
#define INS_REMOVE_BLOB                    0x76
#define INS_BACKUP_DEVICE                  0x78
#define INS_RESTORE_DEVICE                 0x7A
#define INS_BACKUP_COUNTERS                0x7C
#define INS_RESTORE_COUNTERS               0x7E
#ifdef SODER    //TODO: remove if not necessary
#define INS_BACKUP_CREDENTIAL              0x80
#define INS_RESTORE_CREDENTIAL             0x82
#endif
#define INS_GET_INFO                       0x84
#define INS_NOTHING                        0xBC
#define INS_GET_RESPONSE                   0xC0




#ifdef __cplusplus
}
#endif


#endif //__DEFS_INS_H
