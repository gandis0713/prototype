cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME main)
set(APP_NAME ${PROJECT_NAME}.out)

set(CMAKE_CXX_STANDARD 17)

project(
  ${PROJECT_NAME}
  LANGUAGES CXX)

set(SOURCES_FILES
src/io/file.cpp
src/utils/path.cpp
main.cpp)

# set compile definitions.
add_compile_definitions(APP_NAME=${APP_NAME})

add_executable(${APP_NAME} ${SOURCES_FILES})

target_include_directories(${APP_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc/")