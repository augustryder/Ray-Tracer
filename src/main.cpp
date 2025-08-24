#include <fstream>
#include <iostream>
#include <ranges>
#include "vec3.h"
#include "color.h"

int main()
{
  constexpr int image_width = 256;
  constexpr int image_height = 256;

  std::ofstream image_file{"image.ppm"};
  if (!image_file.is_open())
    throw std::runtime_error("Could not open image.ppm");

  image_file << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (auto row = 0; row < image_height; ++row)
  {
    std::println("Lines Remaining: {}", image_height - row);
    for (auto col = 0; col < image_width; ++col)
    {
      const double r = static_cast<double>(col) / (image_width - 1);
      const double g = static_cast<double>(row) / (image_height - 1);
      const double b = static_cast<double>(col) / (image_height - 1);
      const auto pixel_color = Color{r, g, b};
      write_color(image_file, pixel_color);
    }
  }
  std::println("Done!");
}
