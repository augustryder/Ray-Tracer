#pragma once

#include "hittable.h"
#include "material.h"
#include "vec3.h"

class Metal : public Material
{
public:
  Metal(Color albedo, double fuzz) : albedo_{albedo}, fuzz_{fuzz} {}

  bool scatter(const Vec3 &in, const hit_record &hit_record, Color &attenuation,
               Vec3 &scattered) const override
  {
    scattered = normalize(perfect_reflection(in, hit_record.normal)) +
                (fuzz_ * random_unit_vector());
    attenuation = albedo_;
    return dot(scattered, hit_record.normal) > 0;
  }

private:
  Color albedo_;
  double fuzz_;
};
