cmake_minimum_required(VERSION 3.22)

project(gpio++ VERSION 4.2)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/CPM.cmake")
CPMAddPackage("gh:chriskohlhoff/asio#asio-1-28-1")
if(asio_ADDED)
	add_library(asio INTERFACE)

	target_include_directories(asio
		INTERFACE ${asio_SOURCE_DIR}/asio/include
	)

	target_compile_definitions(asio
		INTERFACE
			ASIO_STANDALONE
			ASIO_NO_DEPRECATED
	)

	target_link_libraries(asio
		INTERFACE
		Threads::Threads
	)

	if(WIN32)
		# macro see @ https://stackoverflow.com/a/40217291/1746503
		macro(get_win32_winnt version)
			if (CMAKE_SYSTEM_VERSION)
				set(ver ${CMAKE_SYSTEM_VERSION})
				string(REGEX MATCH "^([0-9]+).([0-9])" ver ${ver})
				string(REGEX MATCH "^([0-9]+)" verMajor ${ver})
				if ("${verMajor}" MATCHES "10")
					set(verMajor "A")
					string(REGEX REPLACE "^([0-9]+)" ${verMajor} ver ${ver})
				endif ("${verMajor}" MATCHES "10")
				string(REPLACE "." "" ver ${ver})
				string(REGEX REPLACE "([0-9A-Z])" "0\\1" ver ${ver})
				set(${version} "0x${ver}")
			endif()
		endmacro()

		if(NOT DEFINED _WIN32_WINNT)
			get_win32_winnt(ver)
			set(_WIN32_WINNT ${ver})
		endif()

		message(STATUS "Set _WIN32_WINNET=${_WIN32_WINNT}")

		target_compile_definitions(asio
			INTERFACE
			_WIN32_WINNT=${_WIN32_WINNT}
			WIN32_LEAN_AND_MEAN
		)
	endif()
	target_disable_static_analysis(asio)
endif()

add_subdirectory(common-headers)
add_subdirectory(base)
set_property(TARGET gpio++-base PROPERTY POSITION_INDEPENDENT_CODE ON)

add_subdirectory(generic)

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "^(arm|aarch64)")
    option(BUILD_PIGPIO "Build pigpio backend" ON)
    if(BUILD_PIGPIO)
        add_subdirectory(pigpio)
    endif()
endif()
