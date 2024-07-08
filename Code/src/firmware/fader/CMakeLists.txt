target_sources(${FIRMWARE_TARGET} PRIVATE
    fader.cpp)

target_include_directories(${FIRMWARE_TARGET} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR})