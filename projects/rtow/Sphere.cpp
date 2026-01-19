#include "Sphere.h"

// Calculate intersection with a sphere (quadratic equation with P(t)=A+tb):
// => r^2 = (x - Cx)^2 + (y - Cy)^2 + (z - Cz)^2 = (P - C).(P - C)
// => 0 = t^2 b.b + 2tb.(A - C) + (A - C).(A - C) - r^2
// Substitute b=2h in the quadratic equation:
// => (-b +- sqrt(b^2 - 4ac)) / (2a)
// => (-h +- sqrt(h^2 - ac)) / a
bool Sphere::hit(const Ray &r, double t_min, double t_max,
                 HitRecord &hr) const {
  const Vec3 oc = r.origin() - _center;
  const double a = r.direction().length_squared();
  const double half_b = dot(oc, r.direction());
  const double c = oc.length_squared() - _radius * _radius;
  const double discriminant = half_b * half_b - a * c;

  if (discriminant < 0)
    return false;
  const double sqrtd = sqrt(discriminant);

  // Find the nearest root that lies in the acceptable range
  double root = (-half_b - sqrtd) / a;
  if (root < t_min || root > t_max) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || root > t_max)
      return false;
  }

  hr.t = root;
  hr.p = r.at(hr.t);
  const Vec3 outward_normal = (hr.p - _center) / _radius;
  setFaceNormal(r, outward_normal, hr);
  hr.material = _material;

  return true;
}
