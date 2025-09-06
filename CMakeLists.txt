cmake_minimum_required(VERSION 3.10)
project(calc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
file(GLOB SRC_FILES src/*.cpp)
add_executable(calc ${SRC_FILES})
include_directories(include)
# target_compile_options(calc PRIVATE -Wall -Wextra -pedantic -g)