#pragma once

#include "utils.h"

class Interval
{
public:
  Interval() : min_{+infinity}, max_{-infinity} {}
  Interval(double min, double max) : min_{min}, max_{max} {}

  double min() const { return min_; }
  double max() const { return max_; }

  bool contains(double x, bool exclusive = false) const
  {
    return exclusive ? min_ < x && x < max_ : min_ <= x && x <= max_;
  }

  double clamp(double x) const
  {
    if (x < min_)
      return min_;
    if (x > max_)
      return max_;
    return x;
  }

  static const Interval empty;
  static const Interval universe;

private:
  double min_;
  double max_;
};

inline const Interval Interval::empty = Interval{+infinity, -infinity};
inline const Interval Interval::universe = Interval{-infinity, +infinity};
