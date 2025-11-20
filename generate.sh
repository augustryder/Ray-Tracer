#!/bin/sh

cmake --build build
if [[ "$?" -eq "0" ]]; then
  ./build/raytracer
  magick image.ppm images/last.png
  rm image.ppm
  chafa -s 120x120 images/last.png
fi
