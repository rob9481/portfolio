#include "HittableList.h"

bool HittableList::hit(const Ray &r, double t_min, double t_max,
                       HitRecord &hr) const {
  HitRecord thr;
  bool hit_anything = false;
  double closest_so_far = t_max;

  for (const auto &object : _objects) {
    if (object->hit(r, t_min, closest_so_far, thr)) {
      hit_anything = true;
      closest_so_far = thr.t;
      hr = thr;
    }
  }

  return hit_anything;
}
