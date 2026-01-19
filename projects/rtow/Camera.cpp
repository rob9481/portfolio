#include "Camera.h"

Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 viewUp, double vfov,
               double aspectRatio, double aperture, double focusDistance) {
  const double theta = degrees_to_radians(vfov);
  const double h = tan(theta / 2);
  const double viewportHeight = 2.0 * h;
  const double viewportWidth = aspectRatio * viewportHeight;

  _w = unit_vector(lookFrom - lookAt);
  _u = unit_vector(cross(viewUp, _w));
  _v = cross(_w, _u);

  _origin = lookFrom;
  _horizontal = focusDistance * viewportWidth * _u;
  _vertical = focusDistance * viewportHeight * _v;
  _lowerLeftCorner =
      _origin - _horizontal / 2 - _vertical / 2 - focusDistance * _w;
  _lensRadius = aperture / 2;
}

Ray Camera::getRay(double s, double t) const {
  const Vec3 randVec = _lensRadius * randomInUnitDisk();
  const Vec3 offset = _u * randVec.x() + _v * randVec.y();
  return Ray(_origin + offset, _lowerLeftCorner + s * _horizontal +
                                   t * _vertical - _origin - offset);
}
