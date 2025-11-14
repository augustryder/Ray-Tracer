#pragma once

#include <limits>
#include <random>

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double PI = 3.1415926535897932385;

inline double deg_to_rad(double degrees) { return (degrees / 180.0) * PI; }

inline double random_double()
{
  static std::uniform_real_distribution<double> dist{0.0, 1.0};
  static std::mt19937 generator;
  return dist(generator);
}

// returns a random double in range [min, max)
inline double random_double(double min, double max)
{
  return min + (max - min) * random_double();
}
