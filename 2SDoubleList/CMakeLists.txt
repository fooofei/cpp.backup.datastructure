cmake_minimum_required(VERSION 3.1)
project(CMAKE_DEMO)


set(self_sources 
	"${CMAKE_CURRENT_SOURCE_DIR}/doublelist.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/doublelist.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/doublelist_test.cpp"
)
set(self double_list)

add_executable(${self} ${self_sources})

source_group(files FILES ${self_sources})


if (WIN32)
  target_compile_options(${self} PRIVATE /source-charset:utf-8 /execution-charset:utf-8)
endif()