cmake_minimum_required(VERSION 3.31)
project(Ray-Tracer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

add_executable(raytracer
        src/main.cpp
        include/vec3.h
        include/color.h)
