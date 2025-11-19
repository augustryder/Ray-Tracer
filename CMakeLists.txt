cmake_minimum_required(VERSION 3.31)
project(Ray-Tracer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(TBB REQUIRED)

include_directories(PRIVATE src)

add_executable(raytracer 
  src/main.cpp
)

target_link_libraries(raytracer
  PRIVATE TBB::tbb
)
