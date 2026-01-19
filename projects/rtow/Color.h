#ifndef COLOR_H
#define COLOR_H

#include "Common.h"
#include "Vec3.h"
#include <iostream>

void writeColor(std::ostream &out, Color pixelColor, int samplesPerPixel) {
  double r = pixelColor.x();
  double g = pixelColor.y();
  double b = pixelColor.z();

  // Apply gamma 2 correction factor
  const double scale = 1.0 / samplesPerPixel;
  r = sqrt(r * scale);
  g = sqrt(g * scale);
  b = sqrt(b * scale);

  out << static_cast<int>(256 * clamp(r, 0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(g, 0, 0.999)) << ' '
      << static_cast<int>(256 * clamp(b, 0, 0.999)) << '\n';
}

#endif // COLOR_H
