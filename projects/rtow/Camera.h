#ifndef CAMERA_H
#define CAMERA_H

#include "Common.h"

class Camera {
public:
  // fvov: vertical field of view
  Camera(Point3 lookFrom, Point3 lookAt, Vec3 viewUp, double vfov,
         double aspectRatio, double aperture, double focusDistance);

  Ray getRay(double s, double t) const;

private:
  Point3 _origin;
  Point3 _lowerLeftCorner;
  Vec3 _horizontal;
  Vec3 _vertical;
  Vec3 _u, _v, _w;
  double _lensRadius;
};

#endif // CAMERA_H
