#pragma once

#include "color.h"
#include "hittable.h"

class Material
{
public:
  virtual ~Material() = default;
  virtual bool scatter(const Vec3 &in, const hit_record &hit_record,
                       Color &attenuation, Vec3 &scattered) const
  {
    return false;
  }
};
