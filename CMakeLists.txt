cmake_minimum_required(VERSION 3.23)
project(MyFirstGame C)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(CMAKE_C_STANDARD 11)

add_executable(MyFirstGame main.c)
