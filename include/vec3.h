#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class Vec3 {
public:
  Vec3() : e{0.0, 0.0, 0.0} {}
  Vec3(double x, double y, double z) : e{x, y, z} {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  Vec3 operator-() const { return Vec3{-e[0], -e[1], -e[2]}; }
  double operator[](int i) const { return e[i]; }
  double& operator[](int i) { return e[i]; }

  Vec3& operator+=(const Vec3& other)
  {
    e[0] += other[0];
    e[1] += other[1];
    e[2] += other[2];
    return *this;
  }

  Vec3& operator*=(double scalar)
  {
    e[0] *= scalar;
    e[1] *= scalar;
    e[2] *= scalar;
    return *this;
  }

  Vec3& operator/=(double scalar) { return *this *= 1 / scalar; }

  double length() const { return std::sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }

private:
  double e[3];
};

using Point3 = Vec3;

inline std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
  return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}

inline Vec3 operator+(const Vec3& u, const Vec3& v)
{
  return { u[0] + v[0], u[1] + v[1], u[2] + v[2] };
}

inline Vec3 operator-(const Vec3& u, const Vec3& v)
{
  return { u[0] - v[0], u[1] - v[1], u[2] - v[2] };
}

inline Vec3 operator*(const Vec3& u, double scalar)
{
  return {u[0] * scalar, u[1] * scalar, u[2] * scalar };
}

inline Vec3 operator*(double scalar, const Vec3& v)
{
  return v * scalar;
}

inline Vec3 operator/(const Vec3& u, double scalar)
{
  return u * (1/scalar);
}

inline double dot(const Vec3& u, const Vec3& v)
{
  return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline Vec3 cross(const Vec3& u, const Vec3& v)
{
  return {u[1] * v[2] - u[2] * v[1],
    u[2] * v[0] - u[0] * v[2],
    u[0] * v[1] - u[1] * v[0]
  };
}

inline Vec3 normalize(const Vec3& v) { return v / v.length(); }

#endif //VEC3_H
