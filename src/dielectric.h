#pragma once

#include "hittable.h"
#include "material.h"
#include "utils.h"
#include "vec3.h"
#include <cmath>

class Dielectric : public Material
{
public:
  Dielectric(double n1_over_n2) : n1_over_n2_{n1_over_n2} {}

  bool scatter(const Vec3 &in, const hit_record &hit_record, Color &attenuation,
               Vec3 &scattered) const override
  {
    attenuation = Color{1.0, 1.0, 1.0};

    const double refraction_ratio =
        hit_record.is_outward_face ? n1_over_n2_ : (1.0 / n1_over_n2_);

    const Vec3 unit_in = normalize(in);
    const double cos_theta = std::fmin(dot(-unit_in, hit_record.normal), 1.0);
    const double sin_theta = std::sqrt(1 - cos_theta * cos_theta);

    if (refraction_ratio * sin_theta > 1.0 ||
        reflectance(cos_theta, refraction_ratio) > random_double())
      scattered = perfect_reflection(in, hit_record.normal);
    else
      scattered = refract(in, hit_record.normal, refraction_ratio);
    return true;
  }

private:
  double n1_over_n2_;

  static double reflectance(double cos_theta, double refraction_index)
  {
    const auto r0 =
        std::pow((1 - refraction_index) / (1 + refraction_index), 2);
    return r0 + (1 - r0) * std::pow(1 - cos_theta, 5);
  }
};
