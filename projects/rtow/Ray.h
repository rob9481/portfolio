#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

// A ray is a function P(t) = A + tB, where P is a position
// along a 3D line, A is the origin, and B is the direction.
class Ray {
public:
  Ray() {}
  Ray(const Point3 &origin, const Vec3 &direction)
      : _origin(origin), _direction(direction) {}

  Point3 origin() const { return _origin; }
  Vec3 direction() const { return _direction; }

  Point3 at(double t) const { return _origin + t * _direction; }

private:
  Point3 _origin;
  Vec3 _direction;
};

#endif // RAY_H
