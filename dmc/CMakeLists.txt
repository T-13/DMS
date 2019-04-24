cmake_minimum_required(VERSION 3.1)
project(dmc)

set(CMAKE_CXX_STANDARD 11)

file(GLOB DMC_SRC
    "src/*.h"
    "src/*.cpp"
)

add_executable(dmc ${DMC_SRC})
