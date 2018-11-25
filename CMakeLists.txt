cmake_minimum_required(VERSION 3.10)
project(VMISS)

set(CMAKE_CXX_STANDARD 14)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)
add_executable(
  vmiss
        ${SRC}/main.cpp
)
