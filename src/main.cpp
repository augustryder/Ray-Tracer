#include "color.h"
#include "hittable.h"
#include "ray.h"
#include "sphere.h"
#include "utils.h"
#include "world.h"
#include <fstream>
#include <iostream>
#include <memory>

Color ray_color(const Ray &ray, const World &world)
{
  struct hit_record hit_record;
  if (world.hit(ray, 0.0, infinity, hit_record))
  {
    return 0.5 * (hit_record.normal + Color{1, 1, 1});
  }
  const Vec3 unit_dir = normalize(ray.direction());
  const double a = 0.5 * (unit_dir.y() + 1);
  return a * Color{0.1, 0.2, 0.8} + (1 - a) * Color{1.0, 1.0, 1.0};
}

int main()
{
  // Camera and viewport
  constexpr double aspect_ratio = 16.0 / 9.0;
  constexpr int image_width = 1280;
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

  // Add objects to world
  const auto sphere1 = std::make_shared<Sphere>(Vec3{0, 0, -3}, 1.0);
  const auto sphere2 = std::make_shared<Sphere>(Vec3{0, 1, -3}, 1.0);
  const auto ground = std::make_shared<Sphere>(Vec3{0, -100.5, -3}, 100.0);
  World world{sphere1, sphere2, ground};

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

      const auto pixel_color = ray_color(ray, world);
      write_color(image_file, pixel_color);
    }
  }
  std::println("Done!");
}
