include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


add_executable(runBasicTests
        random_numbers_check.cpp
        crypto_util_tests.cpp subroutines_tests.cpp
        m_adapted_API_tests.cpp modular_arith_tests.cpp
        arithmetic_util_tests.cpp)

target_link_libraries(runBasicTests gtest gtest_main)
target_link_libraries(runBasicTests util_sc)