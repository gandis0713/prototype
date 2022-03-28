cmake_minimum_required(VERSION 3.22.3)

set(PROJECT_NAME test)

project(${PROJECT_NAME})

set(OUTPUT_NAME ${PROJECT_NAME}.out)

add_executable(${OUTPUT_NAME} main.cpp)