project(crypto LANGUAGES C ASM)

add_library(crypto STATIC)

set_target_properties(crypto PROPERTIES LINKER_LANGUAGE C)

set(COMPILE_C_OPTIONS
    -std=gnu11
    -mcpu=real-m300 
    -march=armv8-m.main
    -mfloat-abi=hard
    -mfpu=fpv5-sp-d16
    -mthumb 
    -mlittle-endian
    -fmessage-length=0 
    -fsigned-char 
    -ffunction-sections 
    -fdata-sections
    -O0
    -g3 
    -ggdb
)

set(Crypto_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/AES/Aes_Dma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/AES/AES_Slave.c
    ${CMAKE_CURRENT_SOURCE_DIR}/AES/RTK_dmac.c
    ${CMAKE_CURRENT_SOURCE_DIR}/HMAC/md.c
    ${CMAKE_CURRENT_SOURCE_DIR}/SHA2/Lalu_SHA2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/SHA2/Sha256_api.c
    ${CMAKE_CURRENT_SOURCE_DIR}/SHA2/Sha512_api.c
    ${CMAKE_CURRENT_SOURCE_DIR}/SHA3/keccak.c
    ${CMAKE_CURRENT_SOURCE_DIR}/SHA3/Lalu_SHA3.c
    ${CMAKE_CURRENT_SOURCE_DIR}/SHA3/Sha3.c
    ${CMAKE_CURRENT_SOURCE_DIR}/SHA3/shake.c
)

target_sources(crypto PUBLIC ${Crypto_SRC})

target_include_directories(crypto PUBLIC
    ${CMAKE_SOURCE_DIR}/Crypto
)

target_include_directories(crypto PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/AES/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/HMAC
    ${CMAKE_CURRENT_SOURCE_DIR}/SHA2/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/SHA3/Include
)

target_compile_definitions(crypto PRIVATE
    "RTE_Compiler_IO_STDOUT"
    "RTE_Compiler_IO_STDOUT_User"
    "__RTS5911__"
)

target_compile_options(crypto PRIVATE ${COMPILE_C_OPTIONS})