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

set(${RP2040_CMSIS_INC_DIRECTORIES} "" CACHE INTERNAL "list of all cmsis directorys to include in project" FORCE)
set(${RP2040_CMSIS_SOURCES} "" CACHE INTERNAL "list of all cmsis sources to include in project" FORCE)

include(rp2040)
string(REPLACE " " ";" RP2040_COMMON_COMPILE_FLAGS ${RP2040_COMMON_COMPILE_FLAGS})
set(PROJECT_COMMON_COMPILE_FLAGS "${RP2040_COMMON_COMPILE_FLAGS}" CACHE STRING "" FORCE)

add_subdirectory(cmsis)

add_executable(${PROJECT_NAME}
        ${RP2040_CMSIS_SOURCES}
        boot2/bs2_default_padded_checksummed.S
        src/isr_vectors.cpp
        src/startup.cpp
        src/main.cpp
)

target_compile_options(${PROJECT_NAME} PUBLIC
        ${PROJECT_COMMON_COMPILE_FLAGS}
)

# Make sure TinyUSB can find tusb_config.h
target_include_directories(${PROJECT_NAME} PUBLIC
        PRIVATE ${RP2040_CMSIS_INC_DIRECTORIES}
        ${CMAKE_CURRENT_LIST_DIR}/inc
        ${CMAKE_CURRENT_LIST_DIR})

# pull in common dependencies
target_link_libraries(${PROJECT_NAME}
        ${PROJECT_COMMON_COMPILE_FLAGS}
        -L"${CMAKE_SOURCE_DIR}/linker"
        -T"memmap_default.ld"
        -nostartfiles
        --specs=nano.specs
        --specs=nosys.specs
        -Wl,--gc-sections
        -Wl,--print-memory-usage
        -Wl,-Map=${PROJECT_NAME}.map)

#set the standards use by this target.
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_features(${PROJECT_NAME} PUBLIC c_std_11)

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
)