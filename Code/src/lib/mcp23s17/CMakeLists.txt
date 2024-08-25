# Code/src/lib/mcp23s17/CMakeLists.txt

add_library(mcp23s17 STATIC mcp23s17.cpp)
target_include_directories(mcp23s17 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../pin
)

target_link_libraries(mcp23s17 PUBLIC
    pico_stdlib
    hardware_spi
    hardware_gpio
)