cmake_minimum_required(VERSION 3.12)

#add cmake folder to cmake modules search path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#enable the compile database generation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "export the build rules into a JSON files for clang-tidy" FORCE)

include(toolchain)

project(bare_blink C CXX ASM)

add_subdirectory(cmsis)
add_subdirectory(drivers)

add_executable(${PROJECT_NAME}
        ${RP2040_CMSIS_SOURCES}
        ${RP2040_DRIVERS_SOURCES}
        boot2/bs2_default_padded_checksummed.S
        src/isr_vectors.cpp
        src/startup.cpp
        src/main.cpp
)

target_compile_options(${PROJECT_NAME} PUBLIC
        ${PROJECT_COMMON_COMPILE_FLAGS}
)

message("cmsis path: ${RP2040_CMSIS_INC_DIRECTORIES}")

target_include_directories(${PROJECT_NAME}
        PUBLIC ${RP2040_CMSIS_INC_DIRECTORIES}
        PUBLIC ${RP2040_DRIVERS_INC_DIRECTORIES}
        ${CMAKE_CURRENT_LIST_DIR}/inc
        ${CMAKE_CURRENT_LIST_DIR})

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


set_target_properties( ${PROJECT_NAME} PROPERTIES SUFFIX ".elf" )

#set the standards use by this target.
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_features(${PROJECT_NAME} PUBLIC c_std_11)

#set extra warnings
target_compile_options(${PROJECT_NAME} PUBLIC -Wunused-parameter -Wextra -Wall)

#set optimization
if (${CMAKE_BUILD_TYPE} MATCHES Debug)
  target_compile_options(${PROJECT_NAME} PUBLIC -O0)
else ()
  target_compile_options(${PROJECT_NAME} PUBLIC -O3)
endif ()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf  ${PROJECT_NAME}.hex
        COMMAND ${CMAKE_OBJDUMP} -h -S ${PROJECT_NAME}.elf > ${PROJECT_NAME}.lst
        COMMAND ${CMAKE_NM_UTIL} -C -r --size-sort -S --print-size ${PROJECT_NAME}.elf > ${PROJECT_NAME}.nm
)