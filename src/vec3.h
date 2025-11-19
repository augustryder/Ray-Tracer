#pragma once

#include "utils.h"
#include <cmath>
#include <iostream>

class Vec3
{
public:
  Vec3() : e{0.0, 0.0, 0.0} {}
  Vec3(double x, double y, double z) : e{x, y, z} {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  Vec3 operator-() const { return Vec3{-e[0], -e[1], -e[2]}; }
  double operator[](int i) const { return e[i]; }
  double &operator[](int i) { return e[i]; }

  Vec3 &operator+=(const Vec3 &other)
  {
    e[0] += other[0];
    e[1] += other[1];
    e[2] += other[2];
    return *this;
  }

  Vec3 &operator*=(double scalar)
  {
    e[0] *= scalar;
    e[1] *= scalar;
    e[2] *= scalar;
    return *this;
  }

  Vec3 &operator/=(double scalar) { return (*this *= (1 / scalar)); }

  double length() const
  {
    return std::sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
  }

  bool near_zero() const
  {
    auto s = 1e-8;
    return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) &&
           (std::fabs(e[2]) < s);
  }

private:
  double e[3];
};

using Point3 = Vec3;

inline std::ostream &operator<<(std::ostream &os, const Vec3 &v)
{
  return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v)
{
  return {u[0] + v[0], u[1] + v[1], u[2] + v[2]};
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v)
{
  return {u[0] - v[0], u[1] - v[1], u[2] - v[2]};
}

inline Vec3 operator*(const Vec3 &u, double scalar)
{
  return {u[0] * scalar, u[1] * scalar, u[2] * scalar};
}

inline Vec3 operator*(double scalar, const Vec3 &v) { return v * scalar; }

inline Vec3 operator*(const Vec3 &u, const Vec3 &v)
{
  return {u[0] * v[0], u[1] * v[1], u[2] * v[2]};
}

inline Vec3 operator/(const Vec3 &u, double scalar) { return u * (1 / scalar); }

inline double dot(const Vec3 &u, const Vec3 &v)
{
  return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v)
{
  return {u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2],
          u[0] * v[1] - u[1] * v[0]};
}

inline Vec3 normalize(const Vec3 &v) { return v / v.length(); }

inline Vec3 random_vector()
{
  return Vec3{random_double(), random_double(), random_double()};
}

inline Vec3 random_vector(double min, double max)
{
  return Vec3{random_double(min, max), random_double(min, max),
              random_double(min, max)};
}

inline Vec3 random_unit_vector()
{
  while (true)
  {
    Vec3 v = random_vector(-1, 1);
    auto length_sqrd = v.length() * v.length();
    if (1e-160 < length_sqrd && length_sqrd <= 1)
      return normalize(v);
  }
}

inline Vec3 random_in_unit_disk()
{
  while (true)
  {
    Vec3 v{random_double(-1, 1), random_double(-1, 1), 0};
    if (v.length() * v.length() < 1)
      return v;
  }
}

inline Vec3 random_reflection(const Vec3 &normal)
{
  const Vec3 v = random_unit_vector();
  return (dot(v, normal) >= 0.0) ? v : -v;
}

inline Vec3 perfect_reflection(const Vec3 &in, const Vec3 &normal)
{
  return in - 2 * (dot(in, normal) * normal);
}

// Snell's Law: n1 * sin(theta_1) = n2 * sin(theta_2)
inline Vec3 refract(const Vec3 &in, const Vec3 &normal, double n1_over_n2)
{
  const Vec3 unit_in = normalize(in);
  const double cos_theta = std::fmin(dot(-unit_in, normal), 1.0);
  const Vec3 out_perp = n1_over_n2 * (unit_in + cos_theta * normal);
  const Vec3 out_parallel =
      -std::sqrt(std::fabs(1.0 - out_perp.length() * out_perp.length())) *
      normal;
  return out_perp + out_parallel;
}
