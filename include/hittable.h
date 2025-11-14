#pragma once

#include "ray.h"

struct hit_record
{
  float t;
  Vec3 position;
  Vec3 normal;
  bool is_outward_face;

  void set_face_normal(const Ray &ray, const Vec3 &outward_normal)
  {
    if (dot(ray.direction(), outward_normal) < 0)
      is_outward_face = true;
    else
      is_outward_face = false;
    normal = is_outward_face ? outward_normal : -outward_normal;
  }
};

class Hittable
{
public:
  virtual ~Hittable() = default;
  virtual bool hit(const Ray &ray, double ray_tmin, double ray_tmax,
                   hit_record &hit_record) const = 0;
};
