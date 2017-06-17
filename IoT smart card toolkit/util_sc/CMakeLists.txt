# UTIL SmartCard

include_directories(p2abc_iot_toolkit_include)

set(UTIL_SC_SRC_FILES
        p2abc_iot_toolkit_src/smartcard_common/m_adapted_API.c
        p2abc_iot_toolkit_src/smartcard_common/global_vars.c
        p2abc_iot_toolkit_src/smartcard_common/subroutines.c
        p2abc_iot_toolkit_src/smartcard_common/APDU_handler.c

        p2abc_iot_toolkit_src/smartcard_utils_interface/system_funcs.c
        p2abc_iot_toolkit_src/smartcard_utils_interface/crypto_util.c
        p2abc_iot_toolkit_src/smartcard_utils_interface/arithmetic_util.c
        p2abc_iot_toolkit_src/smartcard_utils_interface/serialize_util.c
        p2abc_iot_toolkit_src/smartcard_utils_interface/APDU_IO_util.c

        #p2abc_iot_toolkit_src/smartcard_external_utilities/arithmetic_implementation_v1.c
        #p2abc_iot_toolkit_src/smartcard_external_utilities/mini-gmp.c

        #p2abc_iot_toolkit_src/smartcard_external_utilities/tiny-AES128.c
        #p2abc_iot_toolkit_src/smartcard_external_utilities/tiny-SHA256.c
        #p2abc_iot_toolkit_src/smartcard_external_utilities/cryptodev-AES128.c
        #p2abc_iot_toolkit_src/smartcard_external_utilities/cryptodev-SHA256.c

        p2abc_iot_toolkit_src/smartcard_external_utilities/cJSON.c

        )

set(UTIL_SC_INCLUDE_FILES
        p2abc_iot_toolkit_include/smartcard_common/defs_types.h
        p2abc_iot_toolkit_include/smartcard_common/defs_consts.h
        p2abc_iot_toolkit_include/smartcard_common/defs_errs.h
        p2abc_iot_toolkit_include/smartcard_common/defs_ins.h
        p2abc_iot_toolkit_include/smartcard_common/abc4T_types.h
        p2abc_iot_toolkit_include/smartcard_common/APDU_types.h
        p2abc_iot_toolkit_include/smartcard_common/m_adapted_API.h
        p2abc_iot_toolkit_include/smartcard_common/global_vars.h
        p2abc_iot_toolkit_include/smartcard_common/subroutines.h
        p2abc_iot_toolkit_include/smartcard_common/APDU_handler.h
        p2abc_iot_toolkit_include/smartcard_utils_interface/APDU_IO_util.h

        p2abc_iot_toolkit_include/smartcard_utils_interface/system_funcs.h
        p2abc_iot_toolkit_include/smartcard_utils_interface/crypto_util.h
        p2abc_iot_toolkit_include/smartcard_utils_interface/arithmetic_util.h
        p2abc_iot_toolkit_include/smartcard_utils_interface/serialize_util.h
        p2abc_iot_toolkit_include/error_codes.h

        #p2abc_iot_toolkit_include/smartcard_external_utilities/arithmetic_implementation_v1.h
        #p2abc_iot_toolkit_include/smartcard_external_utilities/mini-gmp.h

        #p2abc_iot_toolkit_include/smartcard_external_utilities/tiny-AES128.h
        #p2abc_iot_toolkit_include/smartcard_external_utilities/tiny-SHA256.h
        #p2abc_iot_toolkit_include/smartcard_external_utilities/cryptodev.h
        #p2abc_iot_toolkit_include/smartcard_external_utilities/cryptodev-AES128.h
        #p2abc_iot_toolkit_include/smartcard_external_utilities/cryptodev-SHA256.h

        p2abc_iot_toolkit_include/smartcard_external_utilities/base64.h
        p2abc_iot_toolkit_include/smartcard_external_utilities/cJSON.h

        p2abc_iot_toolkit_include/macrologger.h
        ) #CLion/IDEs add header files to project only if explecitly referenced and used

# TODO añadir ficheros con if else según los definitions

add_library(util_sc ${UTIL_SC_SRC_FILES} ${UTIL_SC_INCLUDE_FILES})

add_definitions( -UUSE_CRYPTODEV)

add_definitions( -DUSE_GMP )
target_link_libraries(util_sc gmp)
add_definitions( -DUSE_OPENSSL )
target_link_libraries(util_sc crypto)

target_link_libraries(util_sc m)