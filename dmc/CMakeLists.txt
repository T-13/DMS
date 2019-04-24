cmake_minimum_required(VERSION 3.0)
project(dmc)

file(GLOB DMC_SRC
    "src/*.h"
    "src/*.cpp"
)

add_executable(dmc ${DMC_SRC})
