#!/bin/sh

cmake --build build
if [[ "$?" -eq "0" ]]; then
  ./build/raytracer
  chafa -s 100x100 image.ppm
fi
