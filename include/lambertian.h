#pragma once

#include "hittable.h"
#include "material.h"

class Lambertian : public Material
{
public:
  Lambertian(Color albedo) : albedo_{albedo} {}

  bool scatter(const Vec3 &in, const hit_record &hit_record, Color &attenuation,
               Vec3 &scattered) const override
  {
    scattered = hit_record.normal + random_unit_vector();
    if (scattered.near_zero())
      scattered = hit_record.normal;
    attenuation = albedo_;
    return true;
  }

private:
  Color albedo_;
};
