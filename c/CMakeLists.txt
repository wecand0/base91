cmake_minimum_required(VERSION 3.24)
project(base91 C)

add_executable(base91-c_run main.c)

include_directories(lib)
add_subdirectory(lib)

target_link_libraries(base91-c_run base91-c)
