cmake_minimum_required(VERSION 2.8.1)

project(cmake_demo)

set(self_binary_name test_list)


add_executable(${self_binary_name} 
  ${CMAKE_CURRENT_SOURCE_DIR}/list.c
  ${CMAKE_CURRENT_SOURCE_DIR}/list.h
  ${CMAKE_CURRENT_SOURCE_DIR}/test_list.cpp
)


if(WIN32)
target_compile_options(${self_binary_name} PRIVATE /source-charset:utf-8 /execution-charset:utf-8)
endif()
