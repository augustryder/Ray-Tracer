#pragma once

#include "color.h"
#include "ray.h"
#include "world.h"
#include <fstream>
#include <iostream>

class Camera
{
public:
  Camera() = default;
  Camera(const Vec3 &pos, double aspect_ratio, int image_width)
      : camera_pos_{pos}, aspect_ratio_{aspect_ratio}, image_width_{image_width}
  {
  }

  void render(const World &world) const
  {
    std::ofstream image_file{"image.ppm"};
    if (!image_file.is_open())
      throw std::runtime_error("Could not open image.ppm");

    image_file << "P3\n" << image_width_ << " " << image_height_ << "\n255\n";

    for (auto row = 0; row < image_height_; ++row)
    {
      std::println("Lines Remaining: {}", image_height_ - row);
      for (auto col = 0; col < image_width_; ++col)
      {
        const auto pixel_pos =
            pixel_zero_ + (row * viewport_dv_) + (col * viewport_du_);
        const auto ray_dir = pixel_pos - camera_pos_;
        const Ray ray{camera_pos_, ray_dir};

        const auto pixel_color = ray_color(ray, world);
        write_color(image_file, pixel_color);
      }
    }
    std::println("Done!");
  }

private:
  Color ray_color(const Ray &ray, const World &world) const
  {
    struct hit_record hit_record;
    if (world.hit(ray, Interval{0, infinity}, hit_record))
    {
      return 0.5 * (hit_record.normal + Color{1, 1, 1});
    }
    const Vec3 unit_dir = normalize(ray.direction());
    const double a = 0.5 * (unit_dir.y() + 1);
    return a * Color{0.1, 0.2, 0.8} + (1 - a) * Color{1.0, 1.0, 1.0};
  }

  Vec3 camera_pos_{0, 0, 0};
  double aspect_ratio_ = 16.0 / 9.0;
  int image_width_ = 1280;

  const int image_height_ =
      (static_cast<double>(image_width_) / aspect_ratio_ < 1)
          ? 1
          : static_cast<double>(image_width_) / aspect_ratio_;

  const double focal_length_ = 1.0;
  const double viewport_height_ = 2.0;
  const double viewport_width_ =
      viewport_height_ * (static_cast<double>(image_width_) / image_height_);

  const Vec3 viewport_u_{viewport_width_, 0, 0};
  const Vec3 viewport_v_{0, -viewport_height_, 0};

  const Vec3 viewport_du_ = viewport_u_ / image_width_;
  const Vec3 viewport_dv_ = viewport_v_ / image_height_;

  const Vec3 viewport_top_left_ = camera_pos_ + Vec3(0, 0, -focal_length_) +
                                  (-viewport_u_ / 2) + (-viewport_v_ / 2);
  const Vec3 pixel_zero_ =
      viewport_top_left_ + 0.5 * (viewport_du_ + viewport_dv_);
};
