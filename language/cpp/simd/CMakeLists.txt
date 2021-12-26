cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME main)

project(
  ${PROJECT_NAME}
  LANGUAGES CXX)

set(SOURCES_FILES
  main.cpp)

add_executable(${PROJECT_NAME}.out ${SOURCES_FILES})