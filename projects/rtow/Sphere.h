#ifndef SPHERE_H
#define SPHERE_H

#include "Hittable.h"
#include "Vec3.h"

class Sphere : public Hittable {
public:
  Sphere() {}
  Sphere(const Point3 &center, double radius, std::shared_ptr<Material> m)
      : _center(center), _radius(radius), _material(m) {}

  bool hit(const Ray &, double t_min, double t_max, HitRecord &) const override;

private:
  Point3 _center;
  double _radius;
  std::shared_ptr<Material> _material;
};

#endif // SPHERE_H
