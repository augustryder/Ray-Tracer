#pragma once

#include "hittable.h"
#include "interval.h"
#include <initializer_list>
#include <memory>
#include <vector>

class World : public Hittable
{
public:
  World() = default;
  World(std::initializer_list<std::shared_ptr<Hittable>> objects)
      : hittable_list_{objects}
  {
  }

  void add(std::shared_ptr<Hittable> object)
  {
    hittable_list_.push_back(object);
  }

  void clear() { hittable_list_.clear(); }

  bool hit(const Ray &ray, Interval ray_t,
           struct hit_record &hit_record) const override
  {
    bool hit_anything = false;
    double closest = ray_t.max();
    struct hit_record temp_rec;
    for (const auto &object : hittable_list_)
    {
      if (object->hit(ray, Interval{ray_t.min(), closest}, temp_rec))
      {
        hit_anything = true;
        closest = temp_rec.t;
        hit_record = temp_rec;
      }
    }
    return hit_anything;
  }

private:
  std::vector<std::shared_ptr<Hittable>> hittable_list_;
};
