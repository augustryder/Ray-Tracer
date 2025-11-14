#pragma once

#include "interval.h"
#include "vec3.h"
#include <iostream>

using Color = Vec3;

inline void write_color(std::ostream &os, const Color &color)
{
  const auto r = color.x();
  const auto g = color.y();
  const auto b = color.z();

  static const Interval intensity{0.000, 0.999};
  const int r_byte = static_cast<int>(intensity.clamp(r) * 256);
  const int g_byte = static_cast<int>(intensity.clamp(g) * 256);
  const int b_byte = static_cast<int>(intensity.clamp(b) * 256);
  os << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
}
