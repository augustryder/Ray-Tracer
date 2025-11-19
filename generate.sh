#!/bin/sh

cmake --build build
if [[ "$?" -eq "0" ]]; then
  ./build/raytracer
  magick image.ppm images/image.png
  rm image.ppm
  chafa -s 120x120 images/image.png
fi
