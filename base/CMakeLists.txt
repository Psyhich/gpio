cmake_minimum_required(VERSION 3.1)

project(gpio++-base VERSION 4.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(gpio++-base OBJECT
	chip_base.cpp
	pin_base.cpp
)
target_include_directories(gpio++-base
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/"
)
target_link_libraries(gpio++-base
	PRIVATE
		asio
	PUBLIC
		common-headers
)
