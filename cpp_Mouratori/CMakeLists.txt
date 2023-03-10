cmake_minimum_required(VERSION 3.14)

project(benches LANGUAGES CXX)

#set(CMAKE_CXX_COMPILER clang++)
#set(CMAKE_C_COMPILER clang)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(benchmark REQUIRED)
add_executable(bench1
	main.cpp
	shapes.cpp
	shapes.h
)
add_executable(bench2
	mainCorner.cpp
	shapes.cpp
	shapes.h
)
find_package(benchmark REQUIRED)

target_link_libraries(bench1 benchmark::benchmark)
target_link_libraries(bench2 benchmark::benchmark)
