#include "Material.h"
#include "Hittable.h"

bool Dielectric::scatter(const Ray &rIn, const HitRecord &hr,
                         Color &attenuation, Ray &scattered) const {
  attenuation = Color(1, 1, 1);
  double refractionRatio =
      hr.front_face ? (1.0 / _indexOfRefraction) : _indexOfRefraction;

  const Vec3 unitDirection = unit_vector(rIn.direction());
  const double cosTheta = fmin(dot(-unitDirection, hr.normal), 1.0);
  const double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

  bool cannotRefract = refractionRatio * sinTheta > 1.0;
  Vec3 direction;

  if (cannotRefract || reflectance(cosTheta, refractionRatio) > random_double())
    direction = reflect(unitDirection, hr.normal);
  else
    direction = refract(unitDirection, hr.normal, refractionRatio);

  scattered = Ray(hr.p, direction);
  return true;
}

double Dielectric::reflectance(double cosine, double refIdx) {
  auto r0 = (1 - refIdx) / (1 + refIdx);
  r0 = r0 * r0;
  return r0 + (1 - r0) * pow(1 - cosine, 5);
}

bool Lambertian::scatter(const Ray &rIn, const HitRecord &hr,
                         Color &attenuation, Ray &scattered) const {
  Vec3 scatterDirection = hr.normal + randomUnitVector();

  // Catch degenerate scatter direction
  if (scatterDirection.nearZero()) {
    scatterDirection = hr.normal;
  }

  scattered = Ray(hr.p, scatterDirection);
  attenuation = _albedo;
  return true;
}

bool Metal::scatter(const Ray &rIn, const HitRecord &hr, Color &attenuation,
                    Ray &scattered) const {
  const Vec3 reflected = reflect(unit_vector(rIn.direction()), hr.normal);
  scattered = Ray(hr.p, reflected + _fuzz * randomInUnitSphere());
  attenuation = _albedo;
  return dot(scattered.direction(), hr.normal) > 0;
}
