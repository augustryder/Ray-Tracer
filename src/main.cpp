#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "sphere.h"
#include <fstream>
#include <iostream>

Color ray_color(const Ray &ray)
{
  Vec3 center = Vec3{0, 0, -2.0};
  double radius = 1.0;
  Sphere sphere{center, radius};
  struct hit_record hit_record;
  if (sphere.hit(ray, 0.0, 1000000.0, hit_record))
  {
    Vec3 normal = hit_record.normal;
    return 0.5 * Color{normal.x() + 1, normal.y() + 1, normal.z() + 1};
  }
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

  const Vec3 camera_pos{0, 0, 0};

  constexpr double focal_length = 1.0;
  constexpr double viewport_height = 2.0;
  constexpr double viewport_width =
      viewport_height * (static_cast<double>(image_width) / image_height);

  const Vec3 viewport_u{viewport_width, 0, 0};
  const Vec3 viewport_v{0, -viewport_height, 0};

  const Vec3 viewport_du = viewport_u / image_width;
  const Vec3 viewport_dv = viewport_v / image_height;

  const Vec3 viewport_top_left = camera_pos + Vec3(0, 0, -focal_length) +
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
      const auto ray_dir = pixel_pos - camera_pos;
      const Ray ray{camera_pos, ray_dir};

      const auto pixel_color = ray_color(ray);
      write_color(image_file, pixel_color);
    }
  }
  std::println("Done!");
}
