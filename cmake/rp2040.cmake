#SET(STM_COMMON_COMPILE_FLAGS "-mcpu=cortex-m0 -mthumb -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -fno-stack-protector -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -Wall -Wextra")
SET(RP2040_COMMON_COMPILE_FLAGS "-mcpu=cortex-m0plus -mthumb -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-stack-protector -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -fshort-enums -Wall -Wextra")

SET(CMAKE_C_FLAGS_DEBUG "${COMMON_FLAGS} -ffreestanding -DDEBUG" CACHE INTERNAL "c compiler flags debug")
SET(CMAKE_CXX_FLAGS_DEBUG "${CLANG_CXX_FLAGS} ${COMMON_FLAGS} -DDEBUG" CACHE INTERNAL "cxx compiler flags debug")
SET(CMAKE_ASM_FLAGS_DEBUG "-g3" CACHE INTERNAL "asm compiler flags debug")

SET(CMAKE_C_FLAGS_RELEASE "${COMMON_FLAGS} " CACHE INTERNAL "c compiler flags release")
SET(CMAKE_CXX_FLAGS_RELEASE "${CLANG_CXX_FLAGS} ${COMMON_FLAGS}" CACHE INTERNAL "cxx compiler flags release")
SET(CMAKE_ASM_FLAGS_RELEASE "-g" CACHE INTERNAL "asm compiler flags release")