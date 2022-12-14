cmake_minimum_required(VERSION 3.23)
project(libbase91c)

add_library(${PROJECT_NAME} base91.h base91.c)

include_directories(.)
