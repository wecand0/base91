cmake_minimum_required(VERSION 3.23)
project(base91-cpp)

set(LIBRARY_STATIC OFF)

include_directories(.)
set(SRC base91.cpp base91.h)

if(${LIBRARY_STATIC})
    add_library(${PROJECT_NAME} STATIC ${SRC})
else()
    add_library(${PROJECT_NAME} SHARED ${SRC})
endif()


