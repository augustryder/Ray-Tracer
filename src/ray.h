#pragma once

#include "vec3.h"

class Ray
{
public:
  Ray(const Vec3 &source, const Vec3 &dir) : source_{source}, dir_{dir} {}

  const Vec3 &source() const { return source_; }
  const Vec3 &direction() const { return dir_; }

  Vec3 position(double t) const { return source_ + dir_ * t; }

private:
  Vec3 source_;
  Vec3 dir_;
};
