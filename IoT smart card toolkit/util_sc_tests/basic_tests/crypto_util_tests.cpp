#include <gtest/gtest.h>
#include <p2abc_iot_toolkit_include/smartcard_utils_interface/crypto_util.h>
#include <p2abc_iot_toolkit_include/smartcard_external_utilities/tiny-SHA256.h>


/********************************************************************/
/******************************SHA256********************************/
/********************************************************************/



TEST(SHA256Test, abc){
    BYTE text[] = {"abc"};
    BYTE hash[] = {0xba,0x78,0x16,0xbf,0x8f,0x01,0xcf,0xea,0x41,0x41,0x40,0xde,0x5d,0xae,0x22,0x23,
                                    0xb0,0x03,0x61,0xa3,0x96,0x17,0x7a,0x9c,0xb4,0x10,0xff,0x61,0xf2,0x00,0x15,0xad};
    BYTE buf[32];
    crypto_SHA256(buf, text, strlen((const char *) text) );

    for (int i = 0; i < 32; i++) {
        EXPECT_EQ(buf[i], hash[i]);
    }

    for (int i = 0; i < 32; i++) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (unsigned)buf[i] ;
    }
    std::cout << std::endl;
}


TEST(SHA256Test, abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq) {
    BYTE text[] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
    BYTE hash[32] = {0x24,0x8d,0x6a,0x61,0xd2,0x06,0x38,0xb8,0xe5,0xc0,0x26,0x93,0x0c,0x3e,0x60,0x39,
                                     0xa3,0x3c,0xe4,0x59,0x64,0xff,0x21,0x67,0xf6,0xec,0xed,0xd4,0x19,0xdb,0x06,0xc1};
    BYTE buf[32];
    crypto_SHA256(buf, text, strlen((const char *) text));
    for (int i = 0; i < 32; i++)
        EXPECT_EQ(buf[i], hash[i]);
}


TEST(SHA256Test, Rosettacode) {
    BYTE text[] = {"Rosetta code"};
    BYTE hash[32] = {0x76, 0x4f, 0xaf, 0x5c, 0x61, 0xac, 0x31, 0x5f, 0x14, 0x97, 0xf9, 0xdf, 0xa5,
                                    0x42, 0x71, 0x39, 0x65, 0xb7, 0x85, 0xe5, 0xcc, 0x2f, 0x70, 0x7d, 0x64, 0x68,
                                    0xd7, 0xd1, 0x12, 0x4c, 0xdf, 0xcf};

    BYTE buf[32];
    crypto_SHA256(buf, text, strlen((const char *) text) );

    for (int i = 0; i < 32; i++) {
        EXPECT_EQ(buf[i], hash[i]);
    }
}




/********************************************************************/
/******************************AES128********************************/
/********************************************************************/


TEST(AES128ECBTest, test1) {

}



TEST(AES128CBCTest, test1) {

}