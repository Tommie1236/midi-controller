# Code/src/lib/pin/CMakeLists.txt

add_library(pin STATIC
            gpioPin.cpp
            adcPin.cpp
            pwmPin.cpp)

target_include_directories(pin PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../*
)

target_link_libraries(pin PUBLIC
    pico_stdlib
    hardware_gpio
    hardware_spi
)