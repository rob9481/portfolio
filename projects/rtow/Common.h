#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// constants
constexpr double inf = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// functions
inline double clamp(double x, double min, double max) {
  if (x < min)
    return min;
  if (x > max)
    return max;
  return x;
}

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

// return a random real in [0, 1)
inline double random_double() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

// return a random real in [min, max)
inline double random_double(double min, double max) {
  return min + (max - min) * random_double();
}

// headers
#include "Ray.h"
#include "Vec3.h"

#endif // COMMON_H
