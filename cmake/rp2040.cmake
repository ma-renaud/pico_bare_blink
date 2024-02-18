SET(RP2040_COMMON_COMPILE_FLAGS "-mcpu=cortex-m0plus -mthumb ")

SET(CMAKE_C_FLAGS_DEBUG "${COMMON_FLAGS} -g3" CACHE INTERNAL "c compiler flags debug")
SET(CMAKE_CXX_FLAGS_DEBUG "${COMMON_FLAGS} -g3" CACHE INTERNAL "cxx compiler flags debug")
SET(CMAKE_ASM_FLAGS_DEBUG " " CACHE INTERNAL "asm compiler flags debug")

SET(CMAKE_C_FLAGS_RELEASE "${COMMON_FLAGS} " CACHE INTERNAL "c compiler flags release")
SET(CMAKE_CXX_FLAGS_RELEASE "${COMMON_FLAGS} " CACHE INTERNAL "cxx compiler flags release")
SET(CMAKE_ASM_FLAGS_RELEASE " " CACHE INTERNAL "asm compiler flags release")