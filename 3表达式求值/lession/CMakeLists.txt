
cmake_minimum_required(VERSION 3.1)
project(C_MAKE_DEMO)

if(APPLE)
 set(CMAKE_MACOSX_RPATH 0)
endif()


set(self_binary_name test_value_expr)

set(Source_files 
	${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/LineStack.h
	)

add_executable(${self_binary_name} ${Source_files})


if (WIN32)
  target_compile_options(${self_binary_name} PRIVATE /source-charset:utf-8)
else()
  # fPIC for other library link
  target_compile_options(${self_binary_name} PRIVATE -fPIC)
  target_compile_options(${self_binary_name} PRIVATE -fvisibility=hidden)
  target_compile_options(${self_binary_name} PRIVATE -fno-common )
endif()

# visual studio project tree
source_group(files FILES ${Source_files})
