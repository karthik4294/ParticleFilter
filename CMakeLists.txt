cmake_minimum_required(VERSION 2.8)
project(particle_filter)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

list(APPEND CMAKE_CXX_FLAGS "-std=c++11")

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(OpenCV 2 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(include)

add_library(particleFilter
        src/log.cpp
        src/particle.cpp
	    	src/map.cpp)

target_link_libraries(particleFilter ${Boost_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(runTest src/run_test.cpp)
add_executable(unitTest src/unit_test.cpp)
target_link_libraries(runTest particleFilter)
target_link_libraries(unitTest particleFilter)


	
