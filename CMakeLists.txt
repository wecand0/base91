cmake_minimum_required(VERSION 3.23)
project(base91test)

add_subdirectory(src)

add_executable(${PROJECT_NAME} example/example.cpp)

target_link_libraries(${PROJECT_NAME} libbase91cpp)
target_include_directories(${PROJECT_NAME} PUBLIC src/cpp src/c)
