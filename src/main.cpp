#include "color.h"
#include "ray.h"
#include <fstream>
#include <iostream>

bool hit_sphere(const Vec3 &center, double radius, const Ray &ray)
{
  Vec3 C = center;
  Vec3 Q = ray.source();
  Vec3 d = ray.direction();
  const auto a = dot(d, d);
  const auto b = -2.0 * dot(d, (C - Q));
  const auto c = dot(C - Q, C - Q) - radius * radius;
  const auto discriminant = b * b - 4 * a * c;
  return (discriminant >= 0);
}

Color ray_color(const Ray &ray)
{
  if (hit_sphere(Vec3{0, 0, -1.5}, 1, ray))
    return Color{1, 0, 0};
  const Vec3 unit_dir = normalize(ray.direction());
  const double a = 0.5 * (unit_dir.y() + 1);
  return a * Color{0.1, 0.2, 0.8} + (1 - a) * Color{1.0, 1.0, 1.0};
}

int main()
{
  constexpr double aspect_ratio = 16.0 / 9.0;
  constexpr int image_width = 400;
  constexpr int image_height =
      (static_cast<double>(image_width) / aspect_ratio < 1)
          ? 1
          : static_cast<double>(image_width) / aspect_ratio;

  const Vec3 camera{0, 0, 0};

  constexpr double focal_length = 1.0;
  constexpr double viewport_height = 2.0;
  constexpr double viewport_width =
      viewport_height * (static_cast<double>(image_width) / image_height);

  const Vec3 viewport_u{viewport_width, 0, 0};
  const Vec3 viewport_v{0, -viewport_height, 0};

  const Vec3 viewport_du = viewport_u / image_width;
  const Vec3 viewport_dv = viewport_v / image_height;

  const Vec3 viewport_top_left = camera + Vec3(0, 0, -focal_length) +
                                 (-viewport_u / 2) + (-viewport_v / 2);
  const Vec3 pixel_zero = viewport_top_left + 0.5 * (viewport_du + viewport_dv);

  std::ofstream image_file{"image.ppm"};
  if (!image_file.is_open())
    throw std::runtime_error("Could not open image.ppm");

  image_file << "P3\n" << image_width << " " << image_height << "\n255\n";

  for (auto row = 0; row < image_height; ++row)
  {
    std::println("Lines Remaining: {}", image_height - row);
    for (auto col = 0; col < image_width; ++col)
    {
      const auto pixel_pos =
          pixel_zero + (row * viewport_dv) + (col * viewport_du);
      const auto ray_dir = pixel_pos - camera;
      const Ray ray{camera, ray_dir};

      // const double r = static_cast<double>(col) / (image_width - 1);
      // const double g = static_cast<double>(row) / (image_height - 1);
      // const double b = static_cast<double>(col) / (image_height - 1);
      // const auto pixel_color = Color{r, g, b};
      const auto pixel_color = ray_color(ray);
      write_color(image_file, pixel_color);
    }
  }
  std::println("Done!");
}
