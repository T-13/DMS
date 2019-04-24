cmake_minimum_required(VERSION 3.1)
project(dmc)

set(CMAKE_CXX_STANDARD 14)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

file(GLOB_RECURSE DMC_SRC
    "src/*.h"
    "src/*.cpp"
)

add_executable(dmc ${DMC_SRC})
