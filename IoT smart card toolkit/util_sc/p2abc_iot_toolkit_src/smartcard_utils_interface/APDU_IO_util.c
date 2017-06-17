#include <smartcard_utils_interface/APDU_IO_util.h>
///////////////////////////////////////////////////////////////////////
/********************************************************************/

/*   Implementation that writes to connfd the APDU bytes            */
/*   and delegates to sc_status_io to save the sc status to         */
/*   the same json file from start                                  */
/********************************************************************/
#include <smartcard_common/defs_types.h>
#include <smartcard_common/APDU_types.h>
#include <smartcard_common/global_vars.h>
#include <unistd.h>
#include <macrologger.h>
#include <smartcard_common/subroutines.h>
#include <smartcard_utils_interface/system_funcs.h>
#include <stdlib.h>
#include <error_codes.h>

void output_apdu_response(){
    WORD APDUlength = La + 2;
    APDUlength = rectifyWordEndianness(APDUlength);
    write(connfd, &APDUlength, 2);
    write(connfd, apdu_data.dataout, La);
    write(connfd, &SW1, 1);
    write(connfd, &SW2, 1);
    fsync(connfd);
    LOG_BYTES(apdu_data.dataout, La, "APDU Response");
    LOG_DEBUG("SW = %02X%02X", SW1, SW2);
}


//void serialize_APDU_response(unsigned char* ap_r, int * buf_len){
//    *buf_len = 2 + La; // APDU Response Length
//    mem_cpy(ap_r, apdu_data.dataout, La);
//    unsigned char * p = ap_r;
//    p += La;
//    *p++ = SW1;
//    *p = SW2;
//}

void parse_APDU_command(BYTE *apdu_bytes, int length) {

    // FIXME en vez de exit, deberían enviar una APDUResponse de APDUCommand mal formada (?) ~ OpenSC no lo hace ~

    LOG_BYTES(apdu_bytes, length, "The %d APDU bytes to interpret", length);

    if (length < 4) {
        LOG_ERROR("APDU too short. length = %d", length);
        exit(ERROR_APDU_TOO_SHORT);
    }

    Le = 0;
    La = 0;
    Lc = 0;
    SW1 = 0x90;
    SW2 = 0x00;

    BYTE *ab = apdu_bytes;
    CLA = *ab++;
    INS = *ab++;
    P1 = *ab++;
    P2 = *ab++;
    length -= 4;

    if (!length) {
        // Case 1
        APDU_Case = 1;
        return;
    }

    if (*ab == 0 && length >= 3) {

        // EXTENDED APDU
        LOG_DEBUG("Extended APDU");

        ab++;
        if (length == 3) {
            Le = (*ab++)<<8;
            Le += *ab++;
//            if (Le == 0)
//                Le = 0xffff+1;
// Convert Le to DWORD or like now, we use short responses and GET RESPONSE trick.
            length -= 3;
            APDU_Case = 2;
        }
        else {
            Lc = (*ab++)<<8;
            Lc += *ab++;
            length -= 3;
            if (length < Lc) {
                LOG_ERROR("APDU too short. length = %d", length);
                exit(ERROR_APDU_TOO_SHORT);
            }
            // Copy Lc bytes of data
            mem_cpy(apdu_data.buffer, ab, Lc);

            length -= Lc;
            ab += Lc;

            if (!length) {
                // Case 3
                APDU_Case = 3;
            } else {
                // Case 4
                APDU_Case = 4;

                /* at this point the apdu has a Lc, so Le is on 2 bytes */
                if (length < 2) {
                    LOG_ERROR("APDU too short (need 2 more bytes). length = %d", length);
                    exit(ERROR_APDU_TOO_LONG);
                }
                Le = (*ab++)<<8;
                Le += *ab++;
//                if (Le == 0)
//                    Le = 0xffff+1;
                length -= 2;
            }
        }
    } else {

        // SHORT APDU
        LOG_DEBUG("Short APDU");

        if (length == 1) {
            // Case 2
            APDU_Case = 2;
            Le = *ab++;
//            if (Le == 0)
//                Le = 0xff+1;
            length--;
        } else {
            Lc = *ab++;
            length--;
            if (length < Lc) {
                LOG_ERROR("APDU too short. length = %d", length);
                exit(ERROR_APDU_TOO_SHORT);
            }
            // Copy Lc bytes of data
            mem_cpy(apdu_data.buffer, ab, Lc);

            length -= Lc;
            ab += Lc;

            if (!length) {
                // Case 3
                APDU_Case = 3;
            } else {
                // Case 4
                APDU_Case = 4;
                Le = *ab++;
//                if (Le == 0)
//                    Le = 0xff+1;
                length--;
            }

        }

    }

    if(length) {
        LOG_ERROR("APDU too long. length = %d", length);
        exit(ERROR_APDU_TOO_LONG);
    }

}
