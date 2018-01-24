cmake_minimum_required(VERSION 3.1)
project(DEMO)

set(BINARY_NAME testlist)


set(Source_files_files
	${CMAKE_CURRENT_SOURCE_DIR}/doubly_linked_list.h
	${CMAKE_CURRENT_SOURCE_DIR}/doubly_linked_list.c
	${CMAKE_CURRENT_SOURCE_DIR}/doubly_linked_list_test.cpp

	${CMAKE_CURRENT_SOURCE_DIR}/linux_kernel_list_test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/linux_kernel_list.h
	
	${CMAKE_CURRENT_SOURCE_DIR}/linked_list.h
	${CMAKE_CURRENT_SOURCE_DIR}/linked_list.c
	${CMAKE_CURRENT_SOURCE_DIR}/linked_list_test.cpp
	
	${CMAKE_CURRENT_SOURCE_DIR}/simple_list_in_msvc.h
	${CMAKE_CURRENT_SOURCE_DIR}/simple_list_in_msvc.c
	${CMAKE_CURRENT_SOURCE_DIR}/simple_list_in_msvc_test.cpp
	
	
	#${CMAKE_CURRENT_SOURCE_DIR}/simple_list_in_msvc.c
	#${CMAKE_CURRENT_SOURCE_DIR}/second_rank_pointer_in_list.c
	main.cpp
)



add_executable(${BINARY_NAME} ${Source_files_files})

source_group(files FILES ${Source_files_files})

#target_sources(${BINARY_NAME} PRIVATE )


