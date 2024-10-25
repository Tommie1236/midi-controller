# Code/src/lib/button/CMakeLists.txt

add_library(encoder STATIC encoder.cpp)
target_include_directories(encoder PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../pin
)

target_link_libraries(encoder PUBLIC
    pico_stdlib
)
