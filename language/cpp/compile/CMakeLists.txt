cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME main)

set(CMAKE_CXX_STANDARD 17)
project(
  ${PROJECT_NAME}
  LANGUAGES CXX)

set(SOURCES_FILES
  main.cpp)


find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME}.out ${SOURCES_FILES})

target_link_libraries(main.out PRIVATE Threads::Threads)