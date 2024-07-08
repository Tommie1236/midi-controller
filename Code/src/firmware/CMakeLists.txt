set(FIRMWARE_TARGET firmware)

# add source files
add_executable(${FIRMWARE_TARGET}
  main.cpp
)

# include submodules
add_subdirectory(button)
add_subdirectory(fader)
add_subdirectory(mcp3008)
add_subdirectory(mcp23s17)


# link in libraries (almost every hardware/<blah>.h or pico/<blah>.h is hardware_blah or pico_blah)
target_link_libraries(${FIRMWARE_TARGET} PRIVATE
    pico_stdlib
    hardware_spi
    hardware_gpio
)

# enable usb/uart stdout
pico_enable_stdio_usb(${FIRMWARE_TARGET} 0)
pico_enable_stdio_uart(${FIRMWARE_TARGET} 1)






# compiler flags
target_compile_options(${FIRMWARE_TARGET} PRIVATE 
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    -fno-exceptions 
    -fno-check-new 
    $<$<COMPILE_LANGUAGE:CXX>:-fno-enforce-eh-specs>
    -g 
    -ffunction-sections 
    -fdata-sections 
    -O3
    -funroll-loops 
    -Werror 
    -Wall
)

# preprocessor macros
target_compile_definitions(${FIRMWARE_TARGET} PRIVATE 
    PICO_HEAP_SIZE=2048
    PICO_XOSC_STARTUP_DELAY_MULTIPLIER=64
)

# select linker script
#pico_set_binary_type(${FIRMWARE_TARGET} copy_to_ram)


# create map/bin/hex file etc.
pico_add_extra_outputs(${FIRMWARE_TARGET})
#pico_add_dis_output2(${FIRMWARE_TARGET})
  

# linker options
target_link_options(${FIRMWARE_TARGET}
    PRIVATE "LINKER:--print-memory-usage"
)