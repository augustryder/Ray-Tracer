cmake_minimum_required(VERSION 3.31)
project(Ray_Tracer)

set(CMAKE_CXX_STANDARD 23)

include_directories(include)

add_executable(Ray_Tracer
        src/main.cpp
        include/vec3.h
        include/color.h)
