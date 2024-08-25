# Code/src/lib/mcp3008/CMakeLists.txt

add_library(mcp3008 STATIC mcp3008.cpp)
target_include_directories(mcp3008 PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../pin
)

target_link_libraries(mcp3008 PUBLIC
    pico_stdlib
    hardware_spi
    hardware_gpio
)