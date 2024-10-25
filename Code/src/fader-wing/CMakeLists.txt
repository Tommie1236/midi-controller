# Code/src/fader-wing/CMakeLists.txt

# add source files
add_executable(fader-wing
  main.cpp
)

# include submodules



# link in libraries (almost every hardware/<blah>.h or pico/<blah>.h is hardware_blah or pico_blah)
target_link_libraries(fader-wing PRIVATE
    pico_stdlib
    hardware_spi
    hardware_gpio

    button
    fader
    mcp23s17
    mcp3008
    encoder
)

# enable usb/uart stdout
pico_enable_stdio_usb(fader-wing 0)
pico_enable_stdio_uart(fader-wing 1)






# compiler flags
target_compile_options(fader-wing PRIVATE 
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
target_compile_definitions(fader-wing PRIVATE 
    PICO_HEAP_SIZE=2048
    PICO_XOSC_STARTUP_DELAY_MULTIPLIER=64
)

# select linker script
#pico_set_binary_type(fader-wing copy_to_ram)


# create map/bin/hex file etc.
pico_add_extra_outputs(fader-wing)
#pico_add_dis_output2(fader-wing)
  

# linker options
target_link_options(fader-wing
    PRIVATE "LINKER:--print-memory-usage"
)
