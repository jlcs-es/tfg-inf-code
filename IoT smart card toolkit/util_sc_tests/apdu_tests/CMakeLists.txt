include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE_FILES handle_APDU_tests.cpp)

add_executable(runAPDUtests ${SOURCE_FILES})

target_link_libraries(runAPDUtests gtest gtest_main)
target_link_libraries(runAPDUtests util_sc)