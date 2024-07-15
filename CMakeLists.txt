cmake_minimum_required (VERSION 3.20)

# Fixed parameters
set(TOOL_DIR ${CMAKE_SOURCE_DIR}/util)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/RTKToolChain.cmake)
set(RAW_BINFILE_NAME ec_firmware.bin)
set(SIGN_TAG_BIN_FILE_NAME tag.bin)

# User-defined parameters
set(EC_PROJECT RTS5911 CACHE STRING "EC Project Version")
set_property(CACHE EC_PROJECT PROPERTY STRINGS RTS5911 RL6999)
set(SIGN_BIN_FILE_NAME EC_Main_Image.bin CACHE STRING "The filename of generated signed bin")
set(SIGN_BACKUP_BIN_FILE_NAME EC_Failsafe_Image.bin CACHE STRING "The filename of signed backup bin")
set(SIGN_LOAD_ADDRESS 0x200000E0 CACHE STRING "Initial address where bin file is loaded into")
set(SIGN_SLOT_SIZE 0x20000 CACHE STRING "slot size")
set(SIGN_SPI_FREQ 3 CACHE STRING "0: SYSCLK/2 | 1: SYSCLK/4 | 2: SYSCLK/8 | 3: SYSCLK/16")
set_property(CACHE SIGN_SPI_FREQ PROPERTY STRINGS 0 1 2 3)
set(SIGN_SPI_MODE 0x03 CACHE STRING "0x03: Normal Read | 0x0B: Fast Read | 0x3B: Dual Read | 0x6B: Quad Read")
set_property(CACHE SIGN_SPI_MODE PROPERTY STRINGS 0x03 0x0B 0x3B 0x6B)
set(SIGN_TAG0_ADDRESS 0x100 CACHE STRING "Tag0 Address. It should fit 256-Byte boundary alignment")
set(SIGN_TAG1_ADDRESS 0x1000 CACHE STRING "Tag1 Address. It should fit 256-Byte boundary alignment")

project(EC-GCC-Firmware LANGUAGES C ASM)

include(${CMAKE_TOOLCHAIN_FILE})
include(${CMAKE_SOURCE_DIR}/cmake/${EC_PROJECT}.cmake)