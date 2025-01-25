cmake_minimum_required(VERSION 3.5)

project(Checkers)

file(GLOB CPPS src/*.cpp)
file(GLOB HEADERS src/*.h )

add_executable(CheckersExecutable ${CPPS} ${HEADERS})

set_target_properties(
	CheckersExecutable PROPERTIES
	CXX_STANDARD 11
	CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(tests)
