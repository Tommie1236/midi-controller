# Code/src/lib/pin/CMakeLists.txt

add_library(pin STATIC pin.cpp)
target_include_directories(pin PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../mcp23s17
    ${CMAKE_CURRENT_SOURCE_DIR}/../mcp3008
)

target_link_libraries(pin PUBLIC
    pico_stdlib
    hardware_gpio
    hardware_spi
)