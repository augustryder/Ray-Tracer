#pragma once

#include "ray.h"

struct hit_record
{
  float t;
  Vec3 position;
  Vec3 normal;
};

class Hittable
{
public:
  virtual ~Hittable() = default;
  virtual bool hit(const Ray &ray, double ray_tmin, double ray_tmax,
                   hit_record &hit_record) const = 0;
};
