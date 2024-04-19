set(${RP2040_DRIVERS_INC_DIRECTORIES} "" CACHE INTERNAL "list of all drivers directorys to include in project" FORCE)
set(${RP2040_DRIVERS_SOURCES} "" CACHE INTERNAL "list of all drivers sources to include in project" FORCE)

set(incLocalVar ${RP2040_DRIVERS_INC_DIRECTORIES})

list(APPEND incLocalVar
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/interfaces
)

set(RP2040_DRIVERS_INC_DIRECTORIES ${incLocalVar} CACHE INTERNAL "")

add_subdirectory(reset)
add_subdirectory(clocks)
add_subdirectory(gpio)
add_subdirectory(timer)
