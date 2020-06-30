cmake_minimum_required(VERSION 3.8)
project(myShell)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES homework_shell.cpp)
add_executable(myShell ${SOURCE_FILES})