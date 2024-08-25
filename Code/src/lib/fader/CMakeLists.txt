# Code/src/lib/fader/CMakeLists.txt

add_library(fader STATIC fader.cpp)
target_include_directories(fader PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../pin
)

target_link_libraries(fader PUBLIC
    pico_stdlib
    hardware_spi
    hardware_gpio
)