

/********************************************************************/
/******************************* BIOSC ******************************/
/********************************************************************/

/********************************************************************/
/**                   Basic Input Output SmartCard                  */
/** Simple main function to generate a standalone binary to run the */
/* Toolkit using files as I/O.                                      */
/********************************************************************/


#include <smartcard_common/APDU_handler.h>
#include <smartcard_common/global_vars.h>
#include <smartcard_utils_interface/serialize_util.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <p2abc_iot_toolkit_include/error_codes.h>
#include <netinet/in.h>
#include <unistd.h>
#include <macrologger.h>
#include <smartcard_utils_interface/APDU_IO_util.h>
#include <p2abc_iot_toolkit_include/smartcard_utils_interface/crypto_util.h>
#include <p2abc_iot_toolkit_include/smartcard_common/subroutines.h>

void receive_commands(){
/*
 * Read from standard input a byte for the operation:
 *  - 0x01 : APDU received.
 *          Read a WORD for APDU length and then as many bytes as said length.
 *  - 0xff : Close connection.
 *          Finish the loop.
 */
    LOG_DEBUG("Start receive_commands loop");
    BYTE command = 0x00;
    WORD apdu_len;
    BYTE apdu_bytes[MAX_APDU_INPUT_DATA_SIZE];
    while(command != 0xff){
        if(read(connfd, &command, 1) <= 0)
            return;
        if(command == 0x01){    // 0x01 : APDU received
            // Read APDU Length
            if(read(connfd, &apdu_len, 2)<=0)
                return;
            apdu_len = rectifyWordEndianness(apdu_len);
            // Read APDU
            if(read(connfd, apdu_bytes, apdu_len)<=0)
                return;

            // Handle the APDU Command
            handle_APDU(apdu_bytes, apdu_len);
        }
    }
    LOG_DEBUG("Finish connection with FF command");
}


int listen_conn(int port) {

    int sockfd, connfd;
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
        exit(ERROR_SOCKET);
    }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if( bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ){
        exit(ERROR_SOCKET);
    }

    if( listen(sockfd, 5) < 0 ){
        exit(ERROR_SOCKET);
    }

    if ( (connfd = accept(sockfd, (struct sockaddr *)NULL, NULL)) < 0 ){
        exit(ERROR_SOCKET);
    }

    return connfd;
}






void create_json(){
    pin_trials = MAX_PIN_TRIALS;
    puk_trials = MAX_PUK_TRIALS;
    memset(device_id, 0, ID_SIZE);
    x_size = 0;
    memset(device_key, 0, MAX_SMALLINT_SIZE);
    memset(puk, 0, PUK_SIZE);
    memset(pin, 0, PIN_SIZE);
    memset(auth_keys, 0, NUM_AUTH_KEYS*MAX_BIGINT_SIZE);
    memset(auth_keys_sizes, 0, sizeof(WORD)*NUM_AUTH_KEYS);
    memset(buffer, 0, BUFFER_MAX_SIZE);
    buffer_size = 0;
    authData = 0;
    memset(groups, 0, sizeof(GROUP)*NUM_GROUPS);
#if NUM_COUNTERS > 0
    memset(counters, 0, sizeof(COUNTER)*NUM_COUNTERS);
#endif
    memset(issuers, 0, sizeof(ISSUER)*NUM_ISSUERS);
    memset(provers, 0, sizeof(PROVER)*NUM_PROVERS);
    current_prover_id = 0;
    memset(credentials, 0, sizeof(CREDENTIAL)*NUM_CREDS);
    memset(blob_store, 0x00, sizeof(BLOB_STORE_ITEM)*MAX_NUMBER_OF_BLOBS);
    memset(blob_catalog, 0x00, sizeof(BLOB_CATALOG_ITEM)*MAX_NUMBER_OF_BLOBS);
    memset(temp_key, 0, MAX_BIGINT_SIZE);

    mode = MODE_ROOT;

    char * json_string = serialize_smartcard_status();
    FILE * f = fopen( "./status.json", "w+");
    if(f==NULL) exit -1;
    fputs(json_string, f);
    free(json_string);
    fclose(f);
}


int main(int argc, char **argv){

//    if (argc < 2) {
//        printf("Usage: %s smartcard_status_file", argv[0]);
//        return -1;
//    }

    printf("BYTE: %d\n" ,sizeof(BYTE));
    printf("SBYTE: %d\n", sizeof(SBYTE));
    printf("WORD: %d\n", sizeof(WORD));
    printf("SWORD: %d\n", sizeof(SWORD));
    printf("DWORD: %d\n", sizeof(DWORD));
    printf("SDWORD: %d\n", sizeof(SDWORD));


    // init random seed
    crypto_InitSeed(0x1234abcd);

    create_json();

    // Restore the smartcard environment
    json_file = "./status.json";
    init_smartcard_from_json_file(json_file);

    // Open socket and listen on port
    connfd = listen_conn(8888);
    // Loop listening for APDUs
    receive_commands();
    // Close the socket
    close(connfd);

    return 0;

}


// TODO :
//      * Check if there exists "reset" command, meaning that the Commmand-Response Dialogue is finished and it's like
//        unplugging and plugging the smartcard.