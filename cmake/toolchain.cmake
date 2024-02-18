#enable the toolcahin file if not in unit test mode
if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "UTest")
    #Use a specific compiler version here
    set(COMPILER_VERSION_REQUIRED "10.2.1" CACHE STRING "Use the fixed compiler version" FORCE)
    if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/arm-none-eabi-gcc.cmake" CACHE UNINITIALIZED "toolchain file")
    endif()
endif()

include(rp2040)
string(REPLACE " " ";" RP2040_COMMON_COMPILE_FLAGS ${RP2040_COMMON_COMPILE_FLAGS})
set(PROJECT_COMMON_COMPILE_FLAGS "${RP2040_COMMON_COMPILE_FLAGS}" CACHE STRING "" FORCE)