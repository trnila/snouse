cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(snouse C CXX ASM)
pico_sdk_init()

add_executable(snouse src/main.c src/usb_descriptors.c)
target_include_directories(snouse PRIVATE src)
target_link_libraries(snouse PRIVATE pico_stdlib tinyusb_device tinyusb_board)
pico_add_extra_outputs(snouse)
