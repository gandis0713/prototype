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
controller.cpp
file_reader.cpp
main.cpp)

# set compile definitions.
add_compile_definitions(APP_NAME=${APP_NAME})
add_compile_definitions(USE_THREAD=true)
add_compile_definitions(THREAD_COUNT=6)
add_compile_definitions(FILE_COUNT=100)

find_package(Threads REQUIRED)

add_executable(${APP_NAME} ${SOURCES_FILES})

target_link_libraries(${APP_NAME} PRIVATE Threads::Threads)
target_include_directories(${APP_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/inc/")