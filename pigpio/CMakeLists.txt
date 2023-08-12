cmake_minimum_required(VERSION 3.22)
project(gpio++-pigpio VERSION 4.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(gpio++-pigpio SHARED
    chip.cpp
	pin.cpp
	$<TARGET_OBJECTS:gpio++-base>
)
target_link_libraries(gpio++-pigpio
	PRIVATE
		asio
	PUBLIC
		common-headers
)
target_include_directories(gpio++-pigpio
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/"
)
