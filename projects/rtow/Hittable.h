#ifndef HITTABLE_H
#define HITTABLE_H

#include "Common.h"
#include "Ray.h"

class Material;

struct HitRecord {
  Point3 p;
  Vec3 normal;
  std::shared_ptr<Material> material;
  double t;
  bool front_face;
};

inline void setFaceNormal(const Ray &r, const Vec3 &outward_normal,
                          HitRecord &hr) {
  hr.front_face = dot(r.direction(), outward_normal) < 0;
  hr.normal = hr.front_face ? outward_normal : -outward_normal;
}

class Hittable {
public:
  virtual bool hit(const Ray &, double t_min, double t_max,
                   HitRecord &) const = 0;
};

#endif // HITTABLE_H
