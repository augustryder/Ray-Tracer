#include "hittable.h"
#include "interval.h"
#include "vec3.h"

class Sphere : public Hittable
{
public:
  Sphere(const Vec3 &center, double radius)
      : center_{center}, radius_{std::fmax(0, radius)}
  {
  }

  bool hit(const Ray &ray, Interval ray_t,
           hit_record &hit_record) const override
  {
    const Vec3 C = center_;
    const Vec3 Q = ray.source();
    const Vec3 d = ray.direction();
    const double a = dot(d, d);
    const double b = -2.0 * dot(d, (C - Q));
    const double c = dot(C - Q, C - Q) - radius_ * radius_;
    const double discriminant = b * b - 4 * a * c;
    if (discriminant <= 0)
      return false;

    double root = (-b - std::sqrt(discriminant)) / (2.0 * a);
    if (!ray_t.contains(root))
    {
      root = (-b + std::sqrt(discriminant)) / (2.0 * a);
      if (!ray_t.contains(root))
        return false;
    }

    hit_record.t = root;
    hit_record.position = ray.position(hit_record.t);
    const Vec3 outward_normal = (hit_record.position - center_) / radius_;
    hit_record.set_face_normal(ray, outward_normal);

    return true;
  }

private:
  Vec3 center_;
  double radius_;
};
