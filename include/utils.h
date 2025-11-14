#pragma once

#include <limits>

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double PI = 3.1415926535897932385;

inline double deg_to_rad(double degrees) { return (degrees / 180.0) * PI; }
