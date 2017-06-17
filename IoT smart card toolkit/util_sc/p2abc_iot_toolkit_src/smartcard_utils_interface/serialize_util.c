#include <smartcard_utils_interface/serialize_util.h>

/********************************************************************/
/*            Implementation using JSON and Base64/HEX              */
/********************************************************************/
#include <smartcard_common/global_vars.h>
#include <smartcard_external_utilities/base64.h>
#include <smartcard_external_utilities/cJSON.h>
#include <smartcard_utils_interface/system_funcs.h>
#include <error_codes.h>
#include <string.h>


void save_status(){
    save_smartcard_to_json_file(json_file);
}


// USE JSON FILES

void init_smartcard_from_json_file(char * json_file){
    // 1. Open smartcard file
    FILE * f = fopen(json_file, "rb");
    if(f==NULL) exit(ERROR_CANT_OPEN_FILE);
    // 2. Save to array of char
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  //same as rewind(f);
    char * string = (char*)malloc(fsize + 1);
    if(string==NULL) exit(ERROR_CANT_MALLOC);
    if(fread(string, 1, fsize, f) < fsize) exit(ERROR_CANT_READ_FILE);
    string[fsize] = 0;
    // 3. Close smartcard file
    fclose(f);
    // 4. Call serialize_util.h deserialize_smartcart_status
    deserialize_smartcard_status(string);
    // 5. Free allocated string
    free(string);
}

void save_smartcard_to_json_file(char * json_file){
    //TODO secure write : simulate atomic writing
    // 1. Open smartcard file
    FILE * f = fopen(json_file, "w+");
    if(f==NULL) exit(ERROR_CANT_OPEN_FILE);
    // 2. Save to array of char
    char * json_string = serialize_smartcard_status();
    if(json_string==NULL) exit(ERROR_CANT_MALLOC);
    fputs(json_string, f);
    // 3. Close smartcard file
    fclose(f);
    // 4. Free allocated string
    free(json_string);
}



// AUX FUNCTIONS FOR JSON SERIALIZATION

void serialize_BYTE(cJSON * object, char * name, BYTE value){
    char temp_hex_string[3];
    sprintf(temp_hex_string, "%02X", value);
    cJSON_AddStringToObject(object, name, temp_hex_string);
}

void deserialize_BYTE(cJSON * object, char * name, BYTE * val) {
    if(cJSON_HasObjectItem(object, name)){
        cJSON* temp_object = cJSON_GetObjectItem(object, name);
        sscanf(temp_object->valuestring, "%2hhx", val);
    } // if 'name' is not in the JSON, its 'val' is not affected
}


void serialize_WORD(cJSON * object, char * name, WORD value){
    char temp_hex_string[5];
    sprintf(temp_hex_string, "%04X", value);
    cJSON_AddStringToObject(object, name, temp_hex_string);
}


void deserialize_WORD(cJSON * object, char * name, BYTE * val) {
    if(cJSON_HasObjectItem(object, name)){
        cJSON* temp_object = cJSON_GetObjectItem(object, name);
        sscanf(temp_object->valuestring, "%4hx", val);
    } // if 'name' is not in the JSON, its 'val' is not affected
}

void serialize_BYTE_ARRAY(cJSON * object, char * name, BYTE * value, WORD length) {
    int temp_base64_len;
    char * temp_base64 = base64(value, length, &temp_base64_len);  // To Base64, the function allocates memory
    cJSON_AddStringToObject(object, name, temp_base64);    // Add base64 string to JSON
    free(temp_base64);  // free the allocated memory in base64()
}


void deserialize_BYTE_ARRAY(cJSON * object, char * name, BYTE * val, WORD exp_length) {
    if(cJSON_HasObjectItem(object, name)){
        int temp_unbase64_len;
        cJSON * temp_object = cJSON_GetObjectItem(object, name);
        char * temp_unbase64 = unbase64(temp_object->valuestring, strlen(temp_object->valuestring), &temp_unbase64_len);
        if (temp_unbase64_len != exp_length) exit(ERROR_BAD_JSON_VALUE_LENGTH);
        mem_cpy(val, temp_unbase64, temp_unbase64_len);
        free(temp_unbase64);
    }
}





// INTERFACE IMPLEMENTATION


char* serialize_smartcard_status(){

    int i;
    cJSON *root = cJSON_CreateObject();

    // BLOB_STORE_ITEM  blob_store [MAX_NUMBER_OF_BLOBS]
    cJSON* blob_store_json_array = cJSON_CreateArray();
    for(i=0; i < MAX_NUMBER_OF_BLOBS; ++i){
        cJSON * blob_store_item_json = cJSON_CreateObject();
        // BYTE buffer[MAX_BLOB_SIZE]
        serialize_BYTE_ARRAY(blob_store_item_json, "buffer", blob_store[i].buffer, MAX_BLOB_SIZE);

        cJSON_AddItemToArray(blob_store_json_array, blob_store_item_json);
    }
    cJSON_AddItemToObject(root, "blob_store", blob_store_json_array);

    // BLOB_CATALOG_ITEM  blob_catalog [MAX_NUMBER_OF_BLOBS]
    cJSON* blob_catalog_json_array = cJSON_CreateArray();
    for(i=0; i < MAX_NUMBER_OF_BLOBS; ++i){
        cJSON * blob_catalog_item_json = cJSON_CreateObject();
        //BYTE exists
        serialize_BYTE(blob_catalog_item_json, "exists", blob_catalog[i].exists);
        //BYTE uri[MAX_URI_SIZE]
        serialize_BYTE_ARRAY(blob_catalog_item_json, "uri", blob_catalog[i].uri, MAX_URI_SIZE);
        //BYTE uri_size;
        serialize_BYTE(blob_catalog_item_json, "uri_size", blob_catalog[i].uri_size);
        //WORD buffer_size;
        serialize_WORD(blob_catalog_item_json, "buffer_size", blob_catalog[i].buffer_size);

        cJSON_AddItemToArray(blob_catalog_json_array, blob_catalog_item_json);
    }
    cJSON_AddItemToObject(root, "blob_catalog", blob_catalog_json_array);

    // BYTE master_backup_key [MASTER_BACKUP_KEY_SIZE]
    serialize_BYTE_ARRAY(root, "master_backup_key", master_backup_key, MASTER_BACKUP_KEY_SIZE);

    // BYTE root_code[ACCESS_CODE_SIZE]
    serialize_BYTE_ARRAY(root, "root_code", root_code, ACCESS_CODE_SIZE);

    // BYTE resurrection_key[RESURRECTION_KEY_SIZE]
    serialize_BYTE_ARRAY(root, "resurrection_key", resurrection_key, RESURRECTION_KEY_SIZE);

    // BYTE pin_trials
    serialize_BYTE(root, "pin_trials", pin_trials);

    // BYTE puk_trials
    serialize_BYTE(root, "puk_trials", puk_trials);

    // BYTE device_id[ID_SIZE]
    serialize_BYTE_ARRAY(root, "device_id", device_id, ID_SIZE);

    // WORD x_size
    serialize_WORD(root, "x_size", x_size);

    // BYTE device_key[MAX_SMALLINT_SIZE]
    serialize_BYTE_ARRAY(root, "device_key", device_key, MAX_SMALLINT_SIZE);

    // BYTE puk[PUK_SIZE]
    serialize_BYTE_ARRAY(root, "puk", puk, PUK_SIZE);

    // BYTE pin[PIN_SIZE]
    serialize_BYTE_ARRAY(root, "pin", pin, PIN_SIZE);

    // BYTE mode
    serialize_BYTE(root, "mode", mode);

    // BYTE auth_keys[NUM_AUTH_KEYS][MAX_BIGINT_SIZE]
    serialize_BYTE_ARRAY(root, "auth_keys", auth_keys, NUM_AUTH_KEYS*MAX_BIGINT_SIZE);

    // WORD auth_keys_sizes[NUM_AUTH_KEYS]
    serialize_BYTE_ARRAY(root, "auth_keys_sizes", auth_keys_sizes, NUM_AUTH_KEYS);

    // BYTE buffer[BUFFER_MAX_SIZE]
    serialize_BYTE_ARRAY(root, "buffer", buffer, BUFFER_MAX_SIZE);

    // WORD buffer_size
    serialize_WORD(root, "buffer_size", buffer_size);

    // BYTE authData
    serialize_BYTE(root, "authData", authData);

    // GROUP groups[NUM_GROUPS]
    cJSON* groups_json_array = cJSON_CreateArray();
    for(i=0; i < NUM_GROUPS; ++i){
        cJSON * groups_item_json = cJSON_CreateObject();
        // BYTE group_id
        serialize_BYTE(groups_item_json, "group_id", groups[i].group_id);
        // BYTE modulus[MAX_BIGINT_SIZE]
        serialize_BYTE_ARRAY(groups_item_json, "modulus", groups[i].modulus, MAX_BIGINT_SIZE);
        // WORD modulus_size
        serialize_WORD(groups_item_json, "modulus_size", groups[i].modulus_size);
        // BYTE q[MAX_SMALLINT_SIZE]
        serialize_BYTE_ARRAY(groups_item_json, "q", groups[i].q, MAX_SMALLINT_SIZE);
        // WORD q_size
        serialize_WORD(groups_item_json, "q_size", groups[i].q_size);
        // BYTE f[MAX_BIGINT_SIZE]
        serialize_BYTE_ARRAY(groups_item_json, "f", groups[i].f, MAX_BIGINT_SIZE);
        // WORD f_size
        serialize_WORD(groups_item_json, "f_size", groups[i].f_size);
        // BYTE g[NUM_GEN][MAX_BIGINT_SIZE]
        serialize_BYTE_ARRAY(groups_item_json, "g", groups[i].g, NUM_GEN*MAX_BIGINT_SIZE);
        // WORD g_size[NUM_GEN]
        serialize_BYTE_ARRAY(groups_item_json, "g_size", groups[i].g_size, NUM_GEN);
        // BYTE num_generators
        serialize_BYTE(groups_item_json, "num_generators", groups[i].num_generators);

        cJSON_AddItemToArray(groups_json_array, groups_item_json);
    }
    cJSON_AddItemToObject(root, "groups", groups_json_array);

#if NUM_COUNTERS > 0
    // COUNTER counters[NUM_COUNTERS]
    cJSON* counters_json_array = cJSON_CreateArray();
    for(i=0; i < NUM_COUNTERS; ++i){
        cJSON * counters_item_json = cJSON_CreateObject();
        // BYTE counter_id
        serialize_BYTE(counters_item_json, "counter_id", counters[i].counter_id);
        // BYTE key_id
        serialize_BYTE(counters_item_json, "key_id", counters[i].key_id);
        // BYTE index
        serialize_BYTE(counters_item_json, "index", counters[i].index);
        // BYTE threshold
        serialize_BYTE(counters_item_json, "threshold", counters[i].threshold);
        // BYTE cursor[CURSOR_SIZE]
        serialize_BYTE_ARRAY(counters_item_json, "cursor", counters[i].cursor, CURSOR_SIZE);
        // BYTE exists
        serialize_BYTE(counters_item_json, "exists", counters[i].exists);

        cJSON_AddItemToArray(counters_json_array, counters_item_json);
    }
    cJSON_AddItemToObject(root, "counters", counters_json_array);
#endif

    // ISSUER issuers[NUM_ISSUERS]
    cJSON* issuers_json_array = cJSON_CreateArray();
    for(i=0; i < NUM_ISSUERS; ++i){
        cJSON * issuers_item_json = cJSON_CreateObject();
        // BYTE issuer_id
        serialize_BYTE(issuers_item_json, "issuer_id", issuers[i].issuer_id);
        // BYTE group_id
        serialize_BYTE(issuers_item_json, "group_id", issuers[i].group_id);
        // BYTE gen_id_1
        serialize_BYTE(issuers_item_json, "gen_id_1", issuers[i].gen_id_1);
        // BYTE gen_id_2
        serialize_BYTE(issuers_item_json, "gen_id_2", issuers[i].gen_id_2);
        // BYTE numpres
        serialize_BYTE(issuers_item_json, "numpres", issuers[i].numpres);
        // BYTE counter_id
        serialize_BYTE(issuers_item_json, "counter_id", issuers[i].counter_id);
        // BYTE exists
        serialize_BYTE(issuers_item_json, "exists", issuers[i].exists);

        cJSON_AddItemToArray(issuers_json_array, issuers_item_json);
    }
    cJSON_AddItemToObject(root, "issuers", issuers_json_array);


    // PROVER provers[NUM_PROVERS]
    cJSON* provers_json_array = cJSON_CreateArray();
    for(i=0; i < NUM_PROVERS; ++i){
        cJSON * provers_item_json = cJSON_CreateObject();
        // BYTE prover_id
        serialize_BYTE(provers_item_json, "prover_id", provers[i].prover_id);
        // WORD ksize
        serialize_WORD(provers_item_json, "ksize", provers[i].ksize);
        // WORD csize
        serialize_WORD(provers_item_json, "csize", provers[i].csize);
        // BYTE kx[MAX_SMALLINT_SIZE]
        serialize_BYTE_ARRAY(provers_item_json, "kx", provers[i].kx, MAX_SMALLINT_SIZE);
        // BYTE c[HASH_SIZE]
        serialize_BYTE_ARRAY(provers_item_json, "c", provers[i].c, HASH_SIZE);
        // BYTE proofsession[PROOFSESSION_SIZE]
        serialize_BYTE_ARRAY(provers_item_json, "proofsession", provers[i].proofsession, PROOFSESSION_SIZE);
        // BYTE proofstatus
        serialize_BYTE(provers_item_json, "proofstatus", provers[i].proofstatus);
        // BYTE cred_ids[NUM_CREDS]
        serialize_BYTE_ARRAY(provers_item_json, "cred_ids", provers[i].cred_ids, NUM_CREDS);
        // BYTE cred_ids_size
        serialize_BYTE(provers_item_json, "cred_ids_size", provers[i].cred_ids_size);
        // BYTE exists
        serialize_BYTE(provers_item_json, "exists", provers[i].exists);

        cJSON_AddItemToArray(provers_json_array, provers_item_json);
    }
    cJSON_AddItemToObject(root, "provers", provers_json_array);


    // BYTE current_prover_id
    serialize_BYTE(root, "current_prover_id", current_prover_id);

    // CREDENTIAL credentials[NUM_CREDS]
    cJSON* credentials_json_array = cJSON_CreateArray();
    for(i=0; i < NUM_CREDS; ++i){
        cJSON * credentials_item_json = cJSON_CreateObject();
        // BYTE credential_id
        serialize_BYTE(credentials_item_json, "credential_id", credentials[i].credential_id);
        // BYTE issuer_id
        serialize_BYTE(credentials_item_json, "issuer_id", credentials[i].issuer_id);
        // BYTE v[MAX_SMALLINT_SIZE]
        serialize_BYTE_ARRAY(credentials_item_json, "v", credentials[i].v, MAX_SMALLINT_SIZE);
        // BYTE kv[MAX_SMALLINT_SIZE]
        serialize_BYTE_ARRAY(credentials_item_json, "kv", credentials[i].kv, MAX_SMALLINT_SIZE);
        // BYTE status
        serialize_BYTE(credentials_item_json, "status", credentials[i].status);
        // BYTE prescount
        serialize_BYTE(credentials_item_json, "prescount", credentials[i].prescount);
        // WORD v_size
        serialize_WORD(credentials_item_json, "v_size", credentials[i].v_size);
        // WORD kv_size
        serialize_WORD(credentials_item_json, "kv_size", credentials[i].kv_size);
        // BYTE exists
        serialize_BYTE(credentials_item_json, "exists", credentials[i].exists);

        cJSON_AddItemToArray(credentials_json_array, credentials_item_json);
    }
    cJSON_AddItemToObject(root, "credentials", credentials_json_array);

    // BYTE temp_key[MAX_BIGINT_SIZE]
    serialize_BYTE_ARRAY(root, "temp_key", temp_key, MAX_BIGINT_SIZE);


    //// ALL STATIC DATA ADDED

    char * res = cJSON_Print(root);
    // char * res = cJSON_PrintUnformatted(root);

    cJSON_Delete(root);

    return res;

}

void deserialize_smartcard_status(unsigned char * ascii) {
    cJSON * root = cJSON_Parse(ascii);
    int i;

    // BLOB_STORE_ITEM   blob_store[MAX_NUMBER_OF_BLOBS]
    if(cJSON_HasObjectItem(root, "blob_store")){
        cJSON * blob_store_json = cJSON_GetObjectItem(root, "blob_store");
        if ( blob_store_json->type != cJSON_Array || cJSON_GetArraySize(blob_store_json) != MAX_NUMBER_OF_BLOBS )
            exit(ERROR_BAD_JSON_ARRAY_LENGTH);
        for(i=0; i < MAX_NUMBER_OF_BLOBS; ++i){
            cJSON * blob_store_item_json = cJSON_GetArrayItem(blob_store_json, i);
            // BYTE buffer[MAX_BLOB_SIZE]
            deserialize_BYTE_ARRAY(blob_store_item_json, "buffer", blob_store[i].buffer, MAX_BLOB_SIZE);
        }
    }

    // BLOB_CATALOG_ITEM blob_catalog[MAX_NUMBER_OF_BLOBS]
    if(cJSON_HasObjectItem(root, "blob_catalog")){
        cJSON * blob_catalog_json = cJSON_GetObjectItem(root, "blob_catalog");
        if ( blob_catalog_json->type != cJSON_Array || cJSON_GetArraySize(blob_catalog_json) != MAX_NUMBER_OF_BLOBS )
            exit(ERROR_BAD_JSON_ARRAY_LENGTH);
        for(i=0; i < MAX_NUMBER_OF_BLOBS; ++i){
            cJSON * blob_catalog_item_json = cJSON_GetArrayItem(blob_catalog_json, i);
            // BYTE exists
            deserialize_BYTE(blob_catalog_item_json, "exists", &(blob_catalog[i].exists));
            // BYTE uri[MAX_URI_SIZE]
            deserialize_BYTE_ARRAY(blob_catalog_item_json, "uri", blob_catalog[i].uri, MAX_URI_SIZE);
            // BYTE uri_size
            deserialize_BYTE(blob_catalog_item_json, "uri_size", &(blob_catalog[i].uri_size));
            // WORD buffer_size
            deserialize_WORD(blob_catalog_item_json, "buffer_size", &(blob_catalog[i].buffer_size));
        }
    }

    // BYTE master_backup_key[MASTER_BACKUP_KEY_SIZE]
    deserialize_BYTE_ARRAY(root, "master_backup_key", master_backup_key, MASTER_BACKUP_KEY_SIZE);

    // BYTE root_code[ACCESS_CODE_SIZE]
    deserialize_BYTE_ARRAY(root, "root_code", root_code, ACCESS_CODE_SIZE);

    // BYTE resurrection_key[RESURRECTION_KEY_SIZE]
    deserialize_BYTE_ARRAY(root, "resurrection_key", resurrection_key, RESURRECTION_KEY_SIZE);

    // BYTE pin_trials
    deserialize_BYTE(root, "pin_trials", &pin_trials);

    // BYTE puk_trials
    deserialize_BYTE(root, "puk_trials", &puk_trials);

    // BYTE device_id[ID_SIZE]
    deserialize_BYTE_ARRAY(root, "device_id", device_id, ID_SIZE);

    // WORD x_size
    deserialize_WORD(root, "x_size", &x_size);

    // BYTE device_key[MAX_SMALLINT_SIZE]
    deserialize_BYTE_ARRAY(root, "device_key", device_key, MAX_SMALLINT_SIZE);

    // BYTE puk[PUK_SIZE]
    deserialize_BYTE_ARRAY(root, "puk", puk, PUK_SIZE);

    // BYTE pin[PIN_SIZE]
    deserialize_BYTE_ARRAY(root, "pin", pin, PIN_SIZE);

    // BYTE mode
    deserialize_BYTE(root, "mode", &mode);

    // BYTE auth_keys[NUM_AUTH_KEYS][MAX_BIGINT_SIZE]
    deserialize_BYTE_ARRAY(root, "auth_keys", auth_keys, NUM_AUTH_KEYS*MAX_BIGINT_SIZE);

    // WORD auth_keys_sizes[NUM_AUTH_KEYS]
    deserialize_BYTE_ARRAY(root, "auth_keys_sizes", auth_keys_sizes, NUM_AUTH_KEYS);

    // BYTE buffer[BUFFER_MAX_SIZE]
    deserialize_BYTE_ARRAY(root, "buffer", buffer, BUFFER_MAX_SIZE);

    // WORD buffer_size
    deserialize_WORD(root, "buffer_size", &buffer_size);

    // BYTE authData
    deserialize_BYTE(root, "authData", &authData);

    // GROUP groups[NUM_GROUPS]
    if(cJSON_HasObjectItem(root, "groups")){
        cJSON * groups_json = cJSON_GetObjectItem(root, "groups");
        if ( groups_json->type != cJSON_Array || cJSON_GetArraySize(groups_json) != NUM_GROUPS )
            exit(ERROR_BAD_JSON_ARRAY_LENGTH);
        for(i=0; i < NUM_GROUPS; ++i){
            cJSON * groups_item_json = cJSON_GetArrayItem(groups_json, i);
            // BYTE group_id
            deserialize_BYTE(groups_item_json, "group_id", &(groups[i].group_id));
            // BYTE modulus[MAX_BIGINT_SIZE]
            deserialize_BYTE_ARRAY(groups_item_json, "modulus", groups[i].modulus, MAX_BIGINT_SIZE);
            // WORD modulus_size
            deserialize_WORD(groups_item_json, "modulus_size", &(groups[i].modulus_size));
            // BYTE q[MAX_SMALLINT_SIZE]
            deserialize_BYTE_ARRAY(groups_item_json, "q", groups[i].q, MAX_SMALLINT_SIZE);
            // WORD q_size
            deserialize_WORD(groups_item_json, "q_size", &(groups[i].q_size));
            // BYTE f[MAX_BIGINT_SIZE]
            deserialize_BYTE_ARRAY(groups_item_json, "f", groups[i].f, MAX_BIGINT_SIZE);
            // WORD f_size
            deserialize_WORD(groups_item_json, "f_size", &(groups[i].f_size));
            // BYTE g[NUM_GEN][MAX_BIGINT_SIZE]
            deserialize_BYTE_ARRAY(groups_item_json, "g", groups[i].g, NUM_GEN*MAX_BIGINT_SIZE);
            // WORD g_size[NUM_GEN]
            deserialize_BYTE_ARRAY(groups_item_json, "g_size", groups[i].g_size, NUM_GEN);
            // BYTE num_generators
            deserialize_BYTE(groups_item_json, "num_generators", &(groups[i].num_generators));
        }
    }



#if NUM_COUNTERS > 0
    // COUNTER counters[NUM_COUNTERS]
    if(cJSON_HasObjectItem(root, "counters")){
        cJSON * counters_json = cJSON_GetObjectItem(root, "counters");
        if ( counters_json->type != cJSON_Array || cJSON_GetArraySize(counters_json) != NUM_COUNTERS )
            exit(ERROR_BAD_JSON_ARRAY_LENGTH);
        for(i=0; i < NUM_COUNTERS; ++i){
            cJSON * counters_item_json = cJSON_GetArrayItem(counters_json, i);
            // BYTE counter_id
            deserialize_BYTE(counters_item_json, "counter_id", &(counters[i].counter_id));
            // BYTE key_id
            deserialize_BYTE(counters_item_json, "key_id", &(counters[i].key_id));
            // BYTE index
            deserialize_BYTE(counters_item_json, "index", &(counters[i].index));
            // BYTE threshold
            deserialize_BYTE(counters_item_json, "threshold", &(counters[i].threshold));
            // BYTE cursor[CURSOR_SIZE]
            deserialize_BYTE_ARRAY(counters_item_json, "cursor", counters[i].cursor, CURSOR_SIZE);
            // BYTE exists
            deserialize_BYTE(counters_item_json, "exists", &(counters[i].exists));
        }
    }
#endif
    // ISSUER issuers[NUM_ISSUERS]
    if(cJSON_HasObjectItem(root, "issuers")){
        cJSON * issuers_json = cJSON_GetObjectItem(root, "issuers");
        if ( issuers_json->type != cJSON_Array || cJSON_GetArraySize(issuers_json) != NUM_ISSUERS )
            exit(ERROR_BAD_JSON_ARRAY_LENGTH);
        for(i=0; i < NUM_ISSUERS; ++i){
            cJSON * issuers_item_json = cJSON_GetArrayItem(issuers_json, i);
            // BYTE issuer_id
            deserialize_BYTE(issuers_item_json, "issuer_id", &(issuers[i].issuer_id));
            // BYTE group_id
            deserialize_BYTE(issuers_item_json, "group_id", &(issuers[i].group_id));
            // BYTE gen_id_1
            deserialize_BYTE(issuers_item_json, "gen_id_1", &(issuers[i].gen_id_1));
            // BYTE gen_id_2
            deserialize_BYTE(issuers_item_json, "gen_id_2", &(issuers[i].gen_id_2));
            // BYTE numpres
            deserialize_BYTE(issuers_item_json, "numpres", &(issuers[i].numpres));
            // BYTE counter_id
            deserialize_BYTE(issuers_item_json, "counter_id", &(issuers[i].counter_id));
            // BYTE exists
            deserialize_BYTE(issuers_item_json, "exists", &(issuers[i].exists));
        }
    }

    // PROVER provers[NUM_PROVERS]
    if(cJSON_HasObjectItem(root, "provers")){
        cJSON * provers_json = cJSON_GetObjectItem(root, "provers");
        if ( provers_json->type != cJSON_Array || cJSON_GetArraySize(provers_json) != NUM_PROVERS )
            exit(ERROR_BAD_JSON_ARRAY_LENGTH);
        for(i=0; i < NUM_PROVERS; ++i){
            cJSON * provers_item_json = cJSON_GetArrayItem(provers_json, i);
            // BYTE prover_id
            deserialize_BYTE(provers_item_json, "prover_id", &(provers[i].prover_id));
            // WORD ksize
            deserialize_WORD(provers_item_json, "ksize", &(provers[i].ksize));
            // WORD csize
            deserialize_WORD(provers_item_json, "csize", &(provers[i].csize));
            // BYTE kx[MAX_SMALLINT_SIZE]
            deserialize_BYTE_ARRAY(provers_item_json, "kx", provers[i].kx, MAX_SMALLINT_SIZE);
            // BYTE c[HASH_SIZE]
            deserialize_BYTE_ARRAY(provers_item_json, "c", provers[i].c, HASH_SIZE);
            // BYTE proofsession[PROOFSESSION_SIZE]
            deserialize_BYTE_ARRAY(provers_item_json, "proofsession", provers[i].proofsession, PROOFSESSION_SIZE);
            // BYTE proofstatus
            deserialize_BYTE(provers_item_json, "proofstatus", &(provers[i].proofstatus));
            // BYTE cred_ids[NUM_CREDS]
            deserialize_BYTE_ARRAY(provers_item_json, "cred_ids", provers[i].cred_ids, NUM_CREDS);
            // BYTE cred_ids_size
            deserialize_BYTE(provers_item_json, "cred_ids_size", &(provers[i].cred_ids_size));
            // BYTE exists
            deserialize_BYTE(provers_item_json, "exists", &(provers[i].exists));
        }
    }

    // BYTE current_prover_id
    deserialize_BYTE(root, "current_prover_id", &current_prover_id);

    // CREDENTIAL credentials[NUM_CREDS]
    if(cJSON_HasObjectItem(root, "credentials")){
        cJSON * credentials_json = cJSON_GetObjectItem(root, "credentials");
        if ( credentials_json->type != cJSON_Array || cJSON_GetArraySize(credentials_json) != NUM_CREDS )
            exit(ERROR_BAD_JSON_ARRAY_LENGTH);
        for(i=0; i < NUM_CREDS; ++i){
            cJSON * credentials_item_json = cJSON_GetArrayItem(credentials_json, i);
            // BYTE credential_id
            deserialize_BYTE(credentials_item_json, "credential_id", &(credentials[i].credential_id));
            // BYTE issuer_id
            deserialize_BYTE(credentials_item_json, "issuer_id", &(credentials[i].issuer_id));
            // BYTE v[MAX_SMALLINT_SIZE]
            deserialize_BYTE_ARRAY(credentials_item_json, "v", credentials[i].v, MAX_SMALLINT_SIZE);
            // BYTE kv[MAX_SMALLINT_SIZE]
            deserialize_BYTE_ARRAY(credentials_item_json, "kv", credentials[i].kv, MAX_SMALLINT_SIZE);
            // BYTE status
            deserialize_BYTE(credentials_item_json, "status", &(credentials[i].status));
            // BYTE prescount
            deserialize_BYTE(credentials_item_json, "prescount", &(credentials[i].prescount));
            // WORD v_size
            deserialize_WORD(credentials_item_json, "v_size", &(credentials[i].v_size));
            // WORD kv_size
            deserialize_WORD(credentials_item_json, "kv_size", &(credentials[i].kv_size));
            // BYTE exists
            deserialize_BYTE(credentials_item_json, "exists", &(credentials[i].exists));
        }
    }

    // BYTE temp_key[MAX_BIGINT_SIZE]
    deserialize_BYTE_ARRAY(root, "temp_key", temp_key, MAX_BIGINT_SIZE);

    //// ALL STATIC DATA ADDED

    cJSON_Delete(root);
}



