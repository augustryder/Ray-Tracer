#pragma once

#include "color.h"
#include "hittable.h"
#include "material.h"
#include "ray.h"
#include "utils.h"
#include "vec3.h"
#include "world.h"
#include <fstream>
#include <iostream>

class Camera
{
public:
  Camera() = default;
  Camera(Vec3 pos, double aspect_ratio, int image_width, int sample_rate,
         int max_depth, double vertical_fov, Vec3 look_at, double roll)
      : camera_pos_{pos}, aspect_ratio_{aspect_ratio},
        image_width_{image_width}, sample_rate_{sample_rate},
        max_depth_{max_depth}, vertical_fov_{vertical_fov}, look_at_{look_at},
        roll_{roll}
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
        Color pixel_color{0, 0, 0};
        for (auto s = 0; s < sample_rate_; s++)
        {
          const Ray ray = get_ray(row, col);
          pixel_color += ray_color(ray, max_depth_, world);
        }
        pixel_color /= sample_rate_;
        write_color(image_file, pixel_color);
      }
    }
    std::println("Done!");
  }

private:
  Color ray_color(const Ray &ray, int depth, const World &world) const
  {
    if (depth <= 0)
      return Color{0, 0, 0};

    struct hit_record hit_record;
    if (world.hit(ray, Interval{0.001, infinity}, hit_record))
    {
      Vec3 scattered;
      Color attenuation;
      if (hit_record.material->scatter(ray.direction(), hit_record, attenuation,
                                       scattered))
      {
        const Ray reflected_ray = Ray{hit_record.position, scattered};
        return attenuation * ray_color(reflected_ray, depth - 1, world);
      }
    }

    const Vec3 unit_dir = normalize(ray.direction());
    const double a = 0.5 * (unit_dir.y() + 1);
    return a * Color{0.3, 0.5, 0.8} + (1 - a) * Color{1.0, 1.0, 1.0};
  }

  Ray get_ray(int row, int col) const
  {
    const Vec3 center_pixel =
        pixel_zero_ + (row * viewport_dv_) + (col * viewport_du_);
    const Vec3 dv = random_double(-0.5, 0.5) * viewport_dv_;
    const Vec3 du = random_double(-0.5, 0.5) * viewport_du_;
    const Vec3 sample_position = center_pixel + dv + du;
    const Vec3 sample_dir = sample_position - camera_pos_;
    return Ray{camera_pos_, sample_dir};
  }

  Vec3 camera_pos_{0, 0, 0};
  double aspect_ratio_ = 16.0 / 9.0;
  int image_width_ = 1920;
  int sample_rate_ = 50;
  int max_depth_ = 25;
  double vertical_fov_ = 90;
  Vec3 look_at_{0, 0, -1};
  double roll_ = 0;

  const int image_height_ =
      (static_cast<double>(image_width_) / aspect_ratio_ < 1)
          ? 1
          : static_cast<double>(image_width_) / aspect_ratio_;

  const double focal_length_ = (camera_pos_ - look_at_).length();
  const double h = std::tan(deg_to_rad(vertical_fov_) / 2.0);
  const double viewport_height_ = 2.0 * h * focal_length_;
  const double viewport_width_ =
      viewport_height_ * (static_cast<double>(image_width_) / image_height_);

  Vec3 view_up{-std::sin(deg_to_rad(roll_)), std::cos(deg_to_rad(roll_)), 0};

  const Vec3 w = normalize(camera_pos_ - look_at_);
  const Vec3 u = normalize(cross(view_up, w));
  const Vec3 v = cross(w, u);

  const Vec3 viewport_u_ = viewport_width_ * u;
  const Vec3 viewport_v_ = viewport_height_ * -v;

  const Vec3 viewport_du_ = viewport_u_ / image_width_;
  const Vec3 viewport_dv_ = viewport_v_ / image_height_;

  const Vec3 viewport_top_left_ = camera_pos_ + (-focal_length_ * w) +
                                  (-viewport_u_ / 2) + (-viewport_v_ / 2);
  const Vec3 pixel_zero_ =
      viewport_top_left_ + 0.5 * (viewport_du_ + viewport_dv_);
};
