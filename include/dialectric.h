#pragma once

#include "hittable.h"
#include "material.h"

class Dialectric : public Material
{
public:
  Dialectric(double refraction_index) : refraction_index_{refraction_index} {}

  bool scatter(const Vec3 &in, const hit_record &hit_record, Color &attenuation,
               Vec3 &scattered)
  {
    return false;
  }

private:
  double refraction_index_;

  static double reflectance(double cos_theta, double refraction_index)
  {
    const auto r0 =
        std::pow((1 - refraction_index) / (1 + refraction_index), 2);
    return r0 + (1 - r0) * std::pow(1 - cos_theta, 5);
  }
};
