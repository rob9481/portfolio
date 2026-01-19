#ifndef VEC3_H
#define VEC3_H

#include <array>
#include <cmath>
#include <iostream>

double random_double();
double random_double(double min, double max);

class Vec3 {
public:
  Vec3() : e{0, 0, 0} {}
  Vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
  double operator[](int i) const { return e[i]; }
  double &operator[](int i) { return e[i]; }

  Vec3 &operator+=(const Vec3 &v) {
    for (int i = 0; i < 3; ++i)
      e[i] += v.e[i];
    return *this;
  }

  Vec3 &operator*=(const double t) {
    for (int i = 0; i < 3; ++i)
      e[i] *= t;
    return *this;
  }

  Vec3 operator/=(const double t) { return *this *= 1 / t; }

  double length() const { return std::sqrt(length_squared()); }

  double length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
  }

  bool nearZero() const {
    const auto s = 1e-8;
    return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
  }

  inline static Vec3 random() {
    return Vec3(random_double(), random_double(), random_double());
  }

  inline static Vec3 random(double min, double max) {
    return Vec3(random_double(min, max), random_double(min, max),
                random_double(min, max));
  }

private:
  std::array<double, 3> e;
};

// aliases
using Point3 = Vec3;
using Color = Vec3;

// utilities
inline std::ostream &operator<<(std::ostream &out, const Vec3 &v) {
  return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline Vec3 operator*(double t, const Vec3 &v) {
  return Vec3(t * v.x(), t * v.y(), t * v.z());
}

inline Vec3 operator*(const Vec3 &v, double t) { return t * v; }

inline Vec3 operator/(const Vec3 &v, double t) { return 1 / t * v; }

inline double dot(const Vec3 &u, const Vec3 &v) {
  return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
  return Vec3(u.y() * v.z() - u.z() * v.y(), u.z() * v.x() - u.x() * v.z(),
              u.x() * v.y() - u.y() * v.x());
}

inline Vec3 unit_vector(const Vec3 &v) { return v / v.length(); }

inline Vec3 randomInUnitDisk() {
  while (true) {
    const auto p = Vec3(random_double(-1, 1), random_double(-1, 1), 0);
    if (p.length_squared() >= 1)
      continue;
    return p;
  }
}

inline Vec3 randomInUnitSphere() {
  while (true) {
    const auto point = Vec3::random(-1, 1);
    if (point.length_squared() >= 1)
      continue;
    return point;
  }
}

inline Vec3 randomUnitVector() { return unit_vector(randomInUnitSphere()); }

inline Vec3 randomInHemisphere(const Vec3 &normal) {
  const Vec3 inUnitSphere = randomInUnitSphere();

  // in the same hemisphere as the normal?
  if (dot(inUnitSphere, normal) > 0.0) {
    return inUnitSphere;
  } else {
    return -inUnitSphere;
  }
}

inline Vec3 refract(const Vec3 &uv, const Vec3 &n, double etaIoverEtaT) {
  const auto cosTheta = fmin(dot(-uv, n), 1.0);
  const Vec3 rOutPerp = etaIoverEtaT * (uv + cosTheta * n);
  const Vec3 rOutParallel = -sqrt(fabs(1.0 - rOutPerp.length_squared())) * n;
  return rOutPerp + rOutParallel;
}

inline Vec3 reflect(const Vec3 &v, const Vec3 &normal) {
  return v - 2 * dot(v, normal) * normal;
}

#endif // VEC3_H
