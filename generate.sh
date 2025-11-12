#!/bin/sh

cmake --build build
./build/raytracer
open image.ppm
