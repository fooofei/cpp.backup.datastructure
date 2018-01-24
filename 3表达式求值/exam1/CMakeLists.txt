
cmake_minimum_required(VERSION 3.1)
project(C_MAKE_DEMO)

set(BINARY_NAME test_value_expr1)

set(Source_files 
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/func.cpp

	)

add_executable(${BINARY_NAME} ${Source_files})

source_group(files FILES ${Source_files})

if(WIN32)
	target_compile_options(${BINARY_NAME} PRIVATE /source-charset:utf-8 /execution-charset:utf-8)
endif()