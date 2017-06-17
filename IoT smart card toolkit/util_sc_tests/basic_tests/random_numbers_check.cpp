#include <gtest/gtest.h>
#include <p2abc_iot_toolkit_include/smartcard_common/m_adapted_API.h>
#include <p2abc_iot_toolkit_include/smartcard_utils_interface/crypto_util.h>


TEST(RandomNumberGenerationTest, Gen8Bytesrnd) {

    crypto_InitSeed(1);

    BYTE buffer[8];
    for (int i = 0; i < 8; i++) {
        buffer[i] = 0xff;
    }
    mGetRandomNumber(buffer);

    BYTE bufferExp[8] = { 0xa7, 0xf1, 0xd9, 0x2a, 0x82, 0xc8, 0xd8, 0xfe};

    //EXPECT_EQ(bufferExp, buffer);
    for(int i=0; i<8; i++)
        EXPECT_EQ(bufferExp[i], buffer[i]);

    mGetRandomNumber(buffer);
    BYTE bufferExp2[8] = { 0x43, 0x4d, 0x98, 0x55, 0x8c, 0xe2, 0xb3, 0x47};
    for(int i=0; i<8; i++)
        EXPECT_EQ(bufferExp2[i], buffer[i]);

}
