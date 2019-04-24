cmake_minimum_required(VERSION 3.0)
project(dms)

file(GLOB DMS_SRC
    "*.h"
    "*.cpp"
)

add_executable(dms ${DMS_SRC})
