cmake_minimum_required(VERSION 3.12)

#Enable the foldeer cmake as cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#enable the compile database generation for clang-tidy and other clang tools.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "export the build rules into a JSON files for clang-tidy" FORCE)

#enable the toolcahin file if not in unit test mode
if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "UTest")
  #Use a specific compiler version here
  set(COMPILER_VERSION_REQUIRED "10.2.1" CACHE STRING "Use the fixed compiler version" FORCE)
  if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/arm-none-eabi-gcc.cmake" CACHE UNINITIALIZED "toolchain file")
  endif()
endif()

project(bare_blink C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(pico_binary_info)

add_executable(${PROJECT_NAME}
        boot2/bs2_default_padded_checksummed.S
        linker/crt0.S
        bootrom.c
        main.cpp
)

# Make sure TinyUSB can find tusb_config.h
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/inc
        ${CMAKE_CURRENT_LIST_DIR})

# pull in common dependencies
target_link_libraries(${PROJECT_NAME}
        pico_binary_info
        -L"${CMAKE_SOURCE_DIR}/linker"
        -T"memmap_default.ld"
        -Wl,--print-memory-usage)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
)
