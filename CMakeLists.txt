cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(snouse C CXX ASM)
pico_sdk_init()

add_executable(snouse src/main.c src/usb_descriptors.c)
target_include_directories(snouse PRIVATE src)
target_link_libraries(snouse PRIVATE pico_stdlib tinyusb_device tinyusb_board)
pico_add_extra_outputs(snouse)


function(render_stl_part part)
    SET(OUT_DIR ${CMAKE_BINARY_DIR}/stls/)
    file(MAKE_DIRECTORY ${OUT_DIR})
    SET(OUT ${OUT_DIR}/${part}.stl)
    add_custom_command(
        OUTPUT ${OUT}
        COMMAND openscad -D 'part="${part}"' -o ${OUT} ${CMAKE_SOURCE_DIR}/case.scad
        DEPENDS ${CMAKE_SOURCE_DIR}/case.scad
    )
    add_custom_target(stl_${part} DEPENDS ${OUT})
    add_dependencies(stls stl_${part})
endfunction()

add_custom_target(stls)
render_stl_part("box")
render_stl_part("cover")
render_stl_part("button")
