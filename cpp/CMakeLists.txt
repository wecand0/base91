cmake_minimum_required(VERSION 3.23)
project(base91)

set(CMAKE_CXX_STANDARD 17)

add_executable(base91-cpp_run main.cpp)

include_directories(lib)
add_subdirectory(lib)

target_link_libraries(base91-cpp_run base91-cpp)
add_subdirectory(test)