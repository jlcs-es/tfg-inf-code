#include <gtest/gtest.h>
#include <p2abc_iot_toolkit_include/smartcard_common/subroutines.h>
#include <p2abc_iot_toolkit_include/smartcard_utils_interface/crypto_util.h>
#include <p2abc_iot_toolkit_include/smartcard_common/global_vars.h>
#include <iostream>

TEST(RandomBytesTest, Gen85Bytesrnd) {

    crypto_InitSeed(1);

    BYTE buffer[85];
    for (int i = 0; i < 85; i++) {
        buffer[i] = 0xff;
    }
    getRandomBytes(buffer, 85);

    BYTE bufferExp[85] = { 0xa7, 0xf1, 0xd9, 0x2a, 0x82, 0xc8, 0xd8, 0xfe,
                           0x43, 0x4d, 0x98, 0x55, 0x8c, 0xe2, 0xb3, 0x47,
                           0x17, 0x11, 0x98, 0x54, 0x2f, 0x11, 0x2d, 0x05,
                           0x58, 0xf5, 0x6b, 0xd6, 0x88, 0x07, 0x99, 0x92,
                           0x48, 0x33, 0x62, 0x41, 0xf3, 0x0d, 0x23, 0xe5,
                           0x5f, 0x30, 0xd1, 0xc8, 0xed, 0x61, 0x0c, 0x4b,
                           0x02, 0x35, 0x39, 0x81, 0x84, 0xb8, 0x14, 0xa2,
                           0x9c, 0xb4, 0x5a, 0x67, 0x2a, 0xca, 0xe5, 0x48,
                           0xe9, 0xc5, 0xf1, 0xb0, 0xc4, 0x15, 0x8a, 0xe5,
                           0x9b, 0x4d, 0x39, 0xf6, 0xf7, 0xe8, 0xa1, 0x05,
                           0xd3, 0xfe, 0xed, 0xa5, 0xd5};

    for(int i=0; i<85; i++)
        EXPECT_EQ(bufferExp[i], buffer[i]);

}



TEST(CheckPinTest, TryWrongPin) {
    BYTE pin1[] = {0x12, 0x34, 0x56, 0x78};
    BYTE pin2[] = {0xff, 0xee, 0xdd, 0xcc};
    for(int i=0; i<PIN_SIZE; i++){
        pin[i] = pin1[i];
    }

    for(int j=1; j<MAX_PIN_TRIALS; j++) {
        ::testing::internal::CaptureStderr();
        checkPin(pin2);
        std::string output = ::testing::internal::GetCapturedStderr();
        EXPECT_EQ("40707", output);
    }

    ::testing::internal::CaptureStderr();
    checkPin(pin2);
    std::string output3 = ::testing::internal::GetCapturedStderr();
    EXPECT_EQ("40708", output3);

}



TEST(CheckPukTest, TryWrongPuk) {
    BYTE puk1[] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0};
    BYTE puk2[] = {0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88};
    for(int i=0; i<PUK_SIZE; i++){
        puk[i] = puk1[i];
    }

    for(int j=1; j<MAX_PUK_TRIALS; j++) {
        ::testing::internal::CaptureStderr();
        checkPuk(puk2);
        std::string output = ::testing::internal::GetCapturedStderr();
        EXPECT_EQ("40709", output);
    }

    ::testing::internal::CaptureStderr();
    checkPuk(puk2);
    std::string output3 = ::testing::internal::GetCapturedStderr();
    EXPECT_EQ("40710", output3);

}


TEST(SizeDecodeTest, Value10010110) {
    BYTE s[] = {0x56,0xab};
    EXPECT_EQ(22187, sizeDecode(s));
}


TEST(SizeEncodeTest, Value22187) {
    BYTE exp[] = {0x56, 0xab};
    BYTE s[] = {0xff, 0xff};
    sizeEncode(s, 22187);
    EXPECT_EQ(exp[0], s[0]);
    EXPECT_EQ(exp[1], s[1]);
}

