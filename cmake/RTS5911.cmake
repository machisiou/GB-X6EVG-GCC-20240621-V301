set(RAW_BINFILE_NAME rts5911.bin)

add_executable(rts5911)

set_target_properties(rts5911 PROPERTIES LINKER_LANGUAGE C)

add_subdirectory(${CMAKE_SOURCE_DIR}/Crypto)

add_dependencies(rts5911 crypto)

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

execute_process(
    COMMAND git describe --tags
    RESULT_VARIABLE result
    OUTPUT_VARIABLE PROJECT_VERSION)

string(REGEX REPLACE "\n$" "" PROJECT_VERSION "${PROJECT_VERSION}")

# set(PROJECT_VERSION "v1.8.5")
configure_file(${CMAKE_SOURCE_DIR}/src/system/Ver.c.in ${CMAKE_BINARY_DIR}/generated/system/Ver.c)

set(RTK_SRC
    ${CMAKE_SOURCE_DIR}/src/system/ACPI_Command.c
    ${CMAKE_SOURCE_DIR}/src/system/Debug.c
    ${CMAKE_SOURCE_DIR}/src/system/Flashtool.c
    ${CMAKE_SOURCE_DIR}/src/system/KBC_Command.c
    ${CMAKE_SOURCE_DIR}/src/system/main.c
    ${CMAKE_SOURCE_DIR}/src/system/Memory.c
    ${CMAKE_BINARY_DIR}/generated/system/Ver.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/CRB.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/Oem_fan.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/Oem_battery.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/Oem_gpio.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/Oem_main.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/Oem_event.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/Oem_pmport0.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/Oem_pmport1.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/Oem_pmport2.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/Oem_pmport3.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/Oem_power.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/Oem_KBC_Command.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/Oem_UDPDFW_TI.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/Oem_scan.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/Oem_timer.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/Oem_Peci.c
    ${CMAKE_SOURCE_DIR}/src/oem/crb/ScanTable.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/ACPI.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/DIO.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/DMA.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/EMI.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/eRPMC.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/ESPI_MAFS.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/ESPI_OOB.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/ESPI_SAFS.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/GPIO.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/I2C.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/KBC.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/KBM.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/LED.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/MBX.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/MONOTONIC_COUNTER.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/P80P81.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/PECI.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/PerVW.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/PMPORT0.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/PMPORT1.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/PMPORT2.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/PMPORT3.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/PS2.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/PWM.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/SPI.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/SPIC.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/SYSTEM.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/TACHO.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/TIMER.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/UART.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/core/WDT.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/nvic.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/system_RTS5911.c
    ${CMAKE_SOURCE_DIR}/src/chip/rts5911/startup_RTS5911.S
)

target_sources(rts5911 PUBLIC ${RTK_SRC})

target_include_directories(rts5911 PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Crypto/AES/Include
    ${CMAKE_SOURCE_DIR}/Crypto/HMAC
    ${CMAKE_SOURCE_DIR}/Crypto/SHA2/Include
    ${CMAKE_SOURCE_DIR}/Crypto/SHA3/Include
)

target_compile_definitions(rts5911 PRIVATE
    "RTE_Compiler_IO_STDOUT"
    "RTE_Compiler_IO_STDOUT_User"
    "__RTS5911__"
    # "Cusomter"
)

target_compile_options(rts5911 PRIVATE ${COMPILE_C_OPTIONS})

target_link_libraries (rts5911 crypto m)

target_link_options(rts5911 PRIVATE
    ${COMPILE_C_OPTIONS}
    -T${CMAKE_SOURCE_DIR}/ldscripts/rts5911.ld
    --specs=nosys.specs
    -nostartfiles 
    -Xlinker 
    --gc-sections
    -Wl,-Map,${CMAKE_BINARY_DIR}/EC.map
    -Wl,--start-group -lgcc -lc -lm 
    -Wl,--print-memory-usage
    -Wl,--end-group
)

# Create raw bin file
add_custom_command(TARGET rts5911 POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:rts5911> "${CMAKE_BINARY_DIR}/${RAW_BINFILE_NAME}"
)

# Generate tag address bin
add_custom_command(TARGET rts5911 POST_BUILD
    COMMAND ${TOOL_DIR}/image_tag_gen.exe 
    ${SIGN_TAG0_ADDRESS} 
    ${SIGN_TAG1_ADDRESS}
    ${SIGN_TAG_BIN_FILE_NAME}
)

# Generate signed bin file
add_custom_command(TARGET rts5911 POST_BUILD
    DEPENDS "${CMAKE_BINARY_DIR}/${RAW_BINFILE_NAME}"
    COMMAND ${TOOL_DIR}/imgtool.exe sign 
    --key=${TOOL_DIR}/key1.pem
    --public-key-format=full 
    --align=32 
    --version=0.0.0 
    --header-size=32 
    --load-addr=${SIGN_LOAD_ADDRESS}
    --pad
    --slot-size=${SIGN_SLOT_SIZE} 
    --pad-header 
    --spi-freq=${SIGN_SPI_FREQ}
    --spi-mode=0 
    --spi-rdcmd=${SIGN_SPI_MODE} 
    --dbg-en=0  
    "${CMAKE_BINARY_DIR}/${RAW_BINFILE_NAME}" 
    "${CMAKE_BINARY_DIR}/${SIGN_BIN_FILE_NAME}"
)

# Create a duplicate signed bin as backup
add_custom_command(TARGET rts5911 POST_BUILD
    DEPENDS "${CMAKE_BINARY_DIR}/${SIGN_BIN_FILE_NAME}"
    COMMAND ${CMAKE_COMMAND} -E copy 
    "${CMAKE_BINARY_DIR}/${SIGN_BIN_FILE_NAME}"
    "${CMAKE_BINARY_DIR}/${SIGN_BACKUP_BIN_FILE_NAME}"
)