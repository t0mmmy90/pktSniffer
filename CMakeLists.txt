cmake_minimum_required(VERSION 2.8.9)
project(pktReader)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(pktReader ${SOURCES})

SET(CMAKE_CXX_COMPILER /usr/bin/clang++-6.0)
target_compile_options(pktReader PUBLIC -Wall -Wextra -pedantic -Werror -std=c++17)