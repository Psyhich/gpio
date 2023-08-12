cmake_minimum_required(VERSION 3.22)

project(common-headers VERSION 0.1)

add_library(common-headers INTERFACE)
target_include_directories(common-headers
	INTERFACE
		"${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
