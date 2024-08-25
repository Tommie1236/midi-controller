# Code/src/lib/button/CMakeLists.txt

add_library(button STATIC button.cpp)
target_include_directories(button PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../pin
)

target_link_libraries(button PUBLIC
    pico_stdlib
)