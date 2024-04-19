# Set local variables
set(incLocalVar ${RP2040_DRIVERS_INC_DIRECTORIES})
set(srcLocalVar ${RP2040_DRIVERS_SOURCES})

# Add specific directories to the list
list(APPEND incLocalVar
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add specific source to the list
list(APPEND srcLocalVar
        ${CMAKE_CURRENT_SOURCE_DIR}/timer.cpp
)

# Update the project lists
set(RP2040_DRIVERS_INC_DIRECTORIES ${incLocalVar} CACHE INTERNAL "")
set(RP2040_DRIVERS_SOURCES ${srcLocalVar} CACHE INTERNAL "")
