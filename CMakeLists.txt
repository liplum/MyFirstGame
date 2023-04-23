cmake_minimum_required(VERSION 3.23)
project(MyFirstGame C)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

set(CMAKE_C_STANDARD 11)

add_executable(MyFirstGame src/main.c src/entity.h src/entity.c src/game.h src/game.c src/level/level_1.c src/level/level_1.h src/console.h src/console.c src/level/level_2.h src/level/level_2.c src/level/level_3.c src/level/level_3.h src/calculate.c src/calculate.h)

set_target_properties(MyFirstGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
