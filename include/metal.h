#pragma once

#include "hittable.h"
#include "material.h"

class Metal : public Material
{
public:
  Metal(Color albedo) : albedo_{albedo} {}

  bool scatter(const Vec3 &in, const hit_record &hit_record, Color &attenuation,
               Vec3 &scattered) const override
  {
    scattered = perfect_reflection(in, hit_record.normal);
    attenuation = albedo_;
    return true;
  }

private:
  Color albedo_;
};
