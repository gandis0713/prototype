cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME main)
set(APP_NAME ${PROJECT_NAME}.out)

project(
  ${PROJECT_NAME}
  LANGUAGES CXX)

set(SOURCES_FILES
  main.cpp
  controller.cpp
  task.cpp
  thread_pool.cpp
  thread.cpp)

find_package(Threads REQUIRED)

add_executable(${APP_NAME} ${SOURCES_FILES})

target_link_libraries(${APP_NAME} PRIVATE Threads::Threads)