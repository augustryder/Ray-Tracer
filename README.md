# Ray Tracer

A custom parallel ray tracing solution built in C++.

## Features

* **Physically-Based Rendering (PBR):** Implements diffuse (Lambertian), metallic, and dielectric (glass/water) materials.
* **Parallelism:** Utilizes **oneTBB** to distribute rendering across multiple CPU cores.
* **Antialiasing:** Samples each pixel with multiple rays in order to smooth out edges.
* **Depth of Field:** Implements a positionable camera with depth of field, resulting in blurred background objects.

## Example Render

The image below was rendered at 1920x1080 resolution with 100 samples per pixel.

![example_render](https://github.com/augustryder/Ray-Tracer/blob/main/images/1280-100-50.png) 

---

## Building and Running

This project uses **CMake** for configuration and building.

### Prerequisites

You will need the following tools installed:
* **C++23**
* **CMake** (version 3.31 or higher)
* **oneTBB** library (often available via package managers)
* **ImageMagick** (for converting the output `.ppm` file to `.png` for display)
* **chafa** (for displaying the image in the terminal)

### Compilation

1.  **Create a build directory:**
    ```bash
    cmake -S . -B ./build
    ```
2.  **Execute the generate script:**
    ```bash
    ./generate.sh
    ```

This script will:
* Build and run the `raytracer` executable.
* Convert the resulting ppm file into a png.
* Display the image in the terminal.
