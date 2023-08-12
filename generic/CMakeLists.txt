cmake_minimum_required(VERSION 3.22)
project(gpio++ VERSION 4.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(gpio++ SHARED
    chip.cpp
	pin.cpp
	$<TARGET_OBJECTS:gpio++-base>
)
target_include_directories(gpio++
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/"
)
target_link_libraries(gpio++
	PRIVATE
		asio
	PUBLIC
		gpio++-base
		common-headers
)
