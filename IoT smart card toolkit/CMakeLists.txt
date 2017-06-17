cmake_minimum_required(VERSION 3.5)
project(p2abc_iot_toolkit)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#add_definitions( -DTESTING_SC )

# SmartCard CODE
add_subdirectory(util_sc)
include_directories(util_sc util_sc/p2abc_iot_toolkit_include)

# TESTS
add_subdirectory(util_sc_tests)



# MAIN
#set(SOURCE_FILES main.cpp)
set(SOURCE_FILES util_sc/BIOSC.c)

add_executable(p2abc_iot_toolkit ${SOURCE_FILES})
target_link_libraries(p2abc_iot_toolkit util_sc)

include (TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
    message(STATUS "BIG_ENDIAN")
else()
    message(STATUS "LITTLE_ENDIAN")
endif()