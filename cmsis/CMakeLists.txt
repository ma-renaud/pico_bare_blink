# Set local variables
set(srcLocalVar
        ${RP2040_CMSIS_INC_DIRECTORIES}
        ${RP2040_CMSIS_SOURCES}
)

# Add specific directories to the list
list(APPEND incLocalVar
        ${CMAKE_CURRENT_SOURCE_DIR}/core/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/device/raspberrypi/rp2040/inc
)

# Add specific source to the list
list(APPEND srcLocalVar
        ${CMAKE_CURRENT_SOURCE_DIR}/device/raspberrypi/rp2040/src/system_RP2040.cpp
)

# Update the project lists
set(RP2040_CMSIS_INC_DIRECTORIES ${incLocalVar} CACHE INTERNAL "")
set(RP2040_CMSIS_SOURCES ${srcLocalVar} CACHE INTERNAL "")

