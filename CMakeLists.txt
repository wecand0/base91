cmake_minimum_required(VERSION 3.23)
project(base91test)

option(test "Build all tests." OFF) # Makes boolean 'test' available.
if (test)
    add_subdirectory(test)
    enable_testing()
endif ()

add_subdirectory(src)

add_executable(${PROJECT_NAME} example/example.cpp)

target_link_libraries(${PROJECT_NAME} base91)
target_include_directories(${PROJECT_NAME} PUBLIC src)
