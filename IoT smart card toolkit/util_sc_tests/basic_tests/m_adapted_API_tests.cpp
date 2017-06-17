#include <gtest/gtest.h>
#include <p2abc_iot_toolkit_include/smartcard_common/m_adapted_API.h>
#include <p2abc_iot_toolkit_include/smartcard_utils_interface/crypto_util.h>

TEST(BlockCopyTest, CopyFixedLength8Bytes) {
    BYTE bufferDst[8];
    for (int i = 0; i < 8; i++) {
        bufferDst[i] = 0xff;
    }

    BYTE bufferSrc[8] = { 0xa7, 0xf1, 0xd9, 0x2a, 0x82, 0xc8, 0xd8, 0xfe};

    mBlockCopyFixedLength(8, bufferSrc, bufferDst);

    for(int i=0; i<8; i++)
        EXPECT_EQ(bufferSrc[i], bufferDst[i]);
}


TEST(BlockCopyTest, CopyFixedLength80Bytes) {
    BYTE bufferDst[80];
    for (int i = 0; i < 80; i++) {
        bufferDst[i] = 0xff;
    }

    BYTE bufferSrc[80] = { 0xa7, 0xf1, 0xd9, 0x2a, 0x82, 0xc8, 0xd8, 0xfe, 0x09, 0x10,
                           0xa7, 0xf1, 0xd9, 0x2a, 0x82, 0xc8, 0xd8, 0xfe, 0x09, 0x10,
                           0xa7, 0xf1, 0xd9, 0x2a, 0x82, 0xc8, 0xd8, 0xfe, 0x09, 0x10,
                           0xa7, 0xf1, 0xd9, 0x2a, 0x82, 0xc8, 0xd8, 0xfe, 0x09, 0x10,
                           0xa7, 0xf1, 0xd9, 0x2a, 0x82, 0xc8, 0xd8, 0xfe, 0x09, 0x10,
                           0xa7, 0xf1, 0xd9, 0x2a, 0x82, 0xc8, 0xd8, 0xfe, 0x09, 0x10,
                           0xa7, 0xf1, 0xd9, 0x2a, 0x82, 0xc8, 0xd8, 0xfe, 0x09, 0x10,
                           0xa7, 0xf1, 0xd9, 0x2a, 0x82, 0xc8, 0xd8, 0xfe, 0x09, 0x10,
    };

    mBlockCopyFixedLength(80, bufferSrc, bufferDst);

    for(int i=0; i<80; i++)
        EXPECT_EQ(bufferSrc[i], bufferDst[i]);

}
//
//
//TEST(SecureHashTest, SHA256) {
//    BYTE buf[SHA256_BLOCK_SIZE];
//    BYTE text[] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
//    BYTE hash[SHA256_BLOCK_SIZE] = {0x24,0x8d,0x6a,0x61,0xd2,0x06,0x38,0xb8,0xe5,0xc0,0x26,0x93,0x0c,0x3e,0x60,0x39,
//                                    0xa3,0x3c,0xe4,0x59,0x64,0xff,0x21,0x67,0xf6,0xec,0xed,0xd4,0x19,0xdb,0x06,0xc1};
//    mSecureHash(strlen((const char *) text), 32, buf, text);
//    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
//        EXPECT_EQ(hash[i], buf[i]);
//
//}
//
//
//
//TEST(SecureHashTest, Not32) {
//    BYTE buf[SHA256_BLOCK_SIZE];
//    memset(buf, 0xab, SHA256_BLOCK_SIZE); // Fill buf with 0xab
//
//    BYTE text[] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
//
//
//    // Test that mSecureHash does not modify buf if hashLen is not 32
//    mSecureHash(strlen((const char *) text), 20, buf, text);
//    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
//        EXPECT_EQ(0xab, buf[i]);
//    mSecureHash(strlen((const char *) text), 28, buf, text);
//    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
//        EXPECT_EQ(0xab, buf[i]);
//    mSecureHash(strlen((const char *) text), 48, buf, text);
//    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
//        EXPECT_EQ(0xab, buf[i]);
//    mSecureHash(strlen((const char *) text), 64, buf, text);
//    for (int i = 0; i < SHA256_BLOCK_SIZE; i++)
//        EXPECT_EQ(0xab, buf[i]);
//
//}
//
//


TEST(ExitSW, Code101) {
    ::testing::internal::CaptureStderr();
    mExitSW(101);
    std::string output = ::testing::internal::GetCapturedStderr();
    EXPECT_EQ("101", output);
}

