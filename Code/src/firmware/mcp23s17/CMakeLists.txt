target_sources(${FIRMWARE_TARGET} PRIVATE
    mcp23s17.cpp
    pin.cpp)

target_include_directories(${FIRMWARE_TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR})