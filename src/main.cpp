#include <fstream>
#include <iostream>
#include <ranges>

int main()
{
  int image_width = 256;
  int image_height = 256;
  int max_color = 255;

  std::ofstream image_file{"image.ppm"};
  if (!image_file.is_open())
    throw std::runtime_error("Could not open image.ppm");


  image_file << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (const auto row : std::views::iota(0, image_height))
  {
    std::println("Lines Remaining: {}", image_height - row);
    for (const auto col : std::views::iota(0, image_width))
    {
      const double red_scale = static_cast<double>(col) / (image_width - 1);
      const double green_scale = static_cast<double>(row) / (image_height - 1);
      const double blue_scale = 0.8;

      const int r = static_cast<int>(std::round(red_scale * max_color));
      const int g = static_cast<int>(std::round(green_scale * max_color));
      const int b = static_cast<int>(std::round(blue_scale * max_color));
      image_file << r << " " << g << " " << b << "\n";
    }
  }
  std::println("Done!");

}
