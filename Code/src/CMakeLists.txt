# Code/src/CMakeLists.txt

add_subdirectory(lib)

if(BUILD_FIRMWARE)
add_subdirectory(firmware)
endif()

if(BUILD_FADER_WING)
add_subdirectory(fader-wing)
endif()