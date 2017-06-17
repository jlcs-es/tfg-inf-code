#ifndef __ERROR_CODES_H
#define __ERROR_CODES_H

#ifdef __cplusplus
extern "C" {
#endif

#define ERROR_CANT_MALLOC                       11
#define ERROR_SOCKET                            12
#define ERROR_CANT_OPEN_FILE                    21
#define ERROR_CANT_READ_FILE                    22
#define ERROR_BAD_JSON_VALUE_LENGTH             23
#define ERROR_BAD_JSON_ARRAY_LENGTH             24
#define ERROR_APDU_TOO_SHORT                    31
#define ERROR_APDU_TOO_LONG                     32
#define ERROR_OPENSSL                           41

#ifdef __cplusplus
}
#endif

#endif // __ERROR_CODES_H
