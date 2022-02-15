#cmake 최소 버전
cmake_minimum_required(VERSION 3.10.1)
 
#프로젝트 이름
project(semaphore)
  
#CMake 옵션 처리
set(CMAKE_VERBOSE_MAKEFILE ON)
   
#컴파일 옵션 추가
add_compile_options(-std=c++11 -ggdb3 -O3 -Wall)
#-Werror)
    
#define 추가
add_definitions(-D_REENTRANT)
     
#header include 경로
include_directories()
      
#라이브러리 링크 디렉토리 경로
link_directories()
       
#전체 적용될 라이브러리 링크
link_libraries(
    rt
    pthread
)
        
#cmake 변수 처리
file(GLOB main_src "./main.cpp")
         
#라이브러리 생성
#set(OUTPUT_STATIC_LIB "hello")
#add_library(${OUTPUT_STATIC_LIB} STATIC ${all_srcs})

#실행 파일 생성
add_executable(sema ${main_src})

#특정 실행 파일에 적용될 라이브러리 링크추가
#target_link_libraries(server
#    -Wl,--disable-new-dtags
#    -Wl,--rpath,/home/openssl
#)


#실행 파일 생성
#add_executable(client ${client_src})
#target_link_libraries(client
#    -Wl,--disable-new-dtags
#    -Wl,--rpath,/home/openssl
#)