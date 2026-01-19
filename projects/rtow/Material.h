#ifndef MATERIAL_H
#define MATERIAL_H

#include "Common.h"

struct HitRecord;

class Material {
public:
  virtual bool scatter(const Ray &rIn, const HitRecord &hr, Color &attenuation,
                       Ray &scattered) const = 0;
};

class Dielectric : public Material {
public:
  Dielectric(double indexOfRefraction)
      : _indexOfRefraction(indexOfRefraction) {}

  virtual bool scatter(const Ray &rIn, const HitRecord &hr, Color &attenuation,
                       Ray &scattered) const override;

private:
  double _indexOfRefraction;

  // Schlick Approximation (so reflectivity of mirror varies with angle)
  static double reflectance(double cosine, double refIdx);
};

class Lambertian : public Material {
public:
  Lambertian(const Color &albedo) : _albedo(albedo) {}

  virtual bool scatter(const Ray &rIn, const HitRecord &hr, Color &attenuation,
                       Ray &scattered) const override;

private:
  Color _albedo;
};

class Metal : public Material {
public:
  Metal(const Color &albedo, double fuzz) : _albedo(albedo) {
    _fuzz = fuzz < 1 ? fuzz : 1;
  }

  virtual bool scatter(const Ray &rIn, const HitRecord &hr, Color &attenuation,
                       Ray &scattered) const override;

private:
  Color _albedo;
  double _fuzz;
};

#endif // MATERIAL_H
