cmake_minimum_required(VERSION 3.10)
project(MyProject)

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

include_directories(include/)

add_executable(SHELL ${SOURCES})

set_target_properties(SHELL PROPERTIES 
                      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_options(SHELL PRIVATE 
    "-Wall" 
    "-fdiagnostics-color=always"
    "-g"
)