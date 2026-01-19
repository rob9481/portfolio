#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "Hittable.h"
#include <memory>
#include <vector>

class HittableList : public Hittable {
public:
  HittableList() {}
  HittableList(std::shared_ptr<Hittable> object) { add(object); }

  void clear() { _objects.clear(); }
  void add(std::shared_ptr<Hittable> object) { _objects.push_back(object); }

  bool hit(const Ray &, double t_min, double t_max, HitRecord &) const override;

private:
  std::vector<std::shared_ptr<Hittable>> _objects;
};

#endif // HITTABLE_LIST_H
