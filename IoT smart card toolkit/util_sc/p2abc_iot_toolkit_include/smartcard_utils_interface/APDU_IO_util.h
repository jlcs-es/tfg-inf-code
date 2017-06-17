#ifndef __APDU_IO_UTIL_H
#define __APDU_IO_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************/
/*************************** APDU IO Util  ****************************/
/********************************************************************/



void parse_APDU_command(unsigned char *apdu_bytes, int length);


/**
 * Takes the values in the APDU variables and public data
 * and outputs it as APDU Response.
 */
void output_apdu_response();



#ifdef __cplusplus
}
#endif

#endif //__APDU_IO_UTIL_H