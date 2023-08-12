cmake_minimum_required(VERSION 3.22)

project(common-headers VERSION 0.1)

add_library(common-headers INTERFACE)
target_link_libraries(common-headers
	INTERFACE
		"${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
