#ifndef __SUBROUTINES_H
#define __SUBROUTINES_H

#include <smartcard_common/defs_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

#define MIN(a,b) (((a) < (b)) ? (a) : (b))

WORD rectifyWordEndianness(WORD w);
DWORD rectifyDWordEndianness(DWORD dw);

void getRandomBytes(BYTE* buffer, WORD size);
BOOL checkPin(BYTE* tested_pin);
BOOL checkPuk(BYTE* tested_puk);
WORD sizeDecode(BYTE *s);
void sizeEncode(BYTE *s, WORD size);
BOOL getKey(BYTE *key, WORD *key_size, const BYTE key_id);
BOOL publicKeyEncrypt(BYTE* key, WORD key_size);
void encryption(BYTE* dst, WORD* dst_size, const BYTE *src, const WORD src_size, const BYTE *key, const WORD key_size);
BOOL extract(const BYTE *key, const WORD key_size);
BOOL extraction(const BYTE *n, const WORD n_size, BYTE *sig, WORD *sig_size, const BYTE *challenge, const WORD challenge_size);
BOOL checkBufferPrefix(BYTE ins, BYTE *datain, WORD datain_size);
BOOL checkBufferEqual(BYTE ins, BYTE *datain, WORD datain_size);
BYTE groupExists(BYTE group_id);
void getGroupComponent(BYTE group_id, BYTE comptype);
BYTE generatorExists(BYTE group_id, BYTE gen_id);
BOOL getGenerator(BYTE group_id, BYTE gen_id);
BOOL checkAccessCredential(BYTE *pin, BYTE credential_id);
BOOL singleOrDoubleExpo(BYTE issuer_id, BYTE *e1, WORD e1_size, BYTE *e2, WORD e2_size);
BOOL checkAccessSession(BYTE credential_id);
BOOL singleOrDoubleResponse(BYTE issuer_id, BYTE *c, WORD c_size, BYTE *x, WORD x_size, BYTE *kx, WORD kx_size, BYTE *v, WORD v_size, BYTE *kv, WORD kv_size);
BOOL singleResponse(BYTE *k, WORD k_size, BYTE *c, WORD c_size, BYTE *u, WORD u_size, BYTE *q, WORD q_size, BYTE offset);
void scopeExclusiveGenerator(BYTE *scope, WORD scope_size, BYTE *m, WORD m_size, BYTE *f, WORD f_size);
BYTE* accessURI(BYTE *datain, WORD Lc);
void getBlobstoreInformations(WORD* first_available_index, WORD *blobcount, WORD *uri_index, BYTE *uri, BYTE uri_size);
void cipher(BYTE *password, BYTE label);
BOOL decipher(BYTE *device_id_prim, BYTE *password, BYTE label);
void output_large_data(void);

#ifdef __cplusplus
}
#endif

#endif // __SUBROUTINES_H
