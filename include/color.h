#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "vec3.h"

using Color = Vec3;

inline void write_color(std::ostream& os, const Color& color)
{
  const int r = static_cast<int>(color.x() * 255.999);
  const int g = static_cast<int>(color.y() * 255.999);
  const int b = static_cast<int>(color.z() * 255.999);
  os << r << ' ' << g << ' ' << b << '\n';
}

#endif //COLOR_H
