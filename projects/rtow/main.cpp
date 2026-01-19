#include "Camera.h"
#include "Color.h"
#include "Common.h"
#include "HittableList.h"
#include "Material.h"
#include "Sphere.h"
#include <iostream>

// The depth param is necessary to stop the function from recursing,
// otherwise it will stop only when fails to hit something.
Color rayColor(const Ray &r, const Hittable &world, int depth) {
  HitRecord hr;

  if (depth <= 0) {
    return Color(0, 0, 0);
  }

  // Fix shadow acne due to floating point approximation not exactly 0
  if (world.hit(r, 0.001, inf, hr)) {
    Ray scattered;
    Color attenuation;
    if (hr.material->scatter(r, hr, attenuation, scattered))
      return attenuation * rayColor(scattered, world, depth - 1);
    return Color(0, 0, 0);
  }

  Vec3 unit_direction = unit_vector(r.direction());
  // add 1.0 because ymin == -1.0
  double t = 0.5 * (unit_direction.y() + 1.0);
  // linear blend, linear interpolation, lerp (white and blue):
  //   (1-t) * startValue + t * endValue;
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

HittableList randomScene() {
  HittableList world;

  auto materialGround = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
  world.add(
      std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, materialGround));

  for (int a = -11; a < 11; ++a) {
    for (int b = -11; b < 11; ++b) {
      auto chooseMaterial = random_double();
      Point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

      if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
        std::shared_ptr<Material> sphereMaterial;

        if (chooseMaterial < 0.8) {
          // diffuse
          auto albedo = Color::random() * Color::random();
          sphereMaterial = std::make_shared<Lambertian>(albedo);
        } else if (chooseMaterial < 0.95) {
          // metal
          auto albedo = Color::random(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
        } else {
          // glass
          sphereMaterial = std::make_shared<Dielectric>(1.5);
        }

        world.add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
      }
    }
  }

  auto material1 = std::make_shared<Dielectric>(1.5);
  world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

  auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
  world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

  auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0);
  world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

  return world;
}

// 1. Calculate ray from eye to pixel
// 2. Determine which objects ray intersects
// 3. Compute color for each intersection point
int main() {
  // Image
  // Format:
  //   P3
  //   width height
  //   max_color
  //   <width x height grid of RGB colors>
  const double aspectRatio = 3.0 / 2.0;
  const int image_width = 1200;
  const int image_height = static_cast<int>(image_width / aspectRatio);
  const int max_color = 255;
  const int maxDepth = 50;
  const int samplesPerPixel = 500;

  // Camera
  const Point3 lookFrom(12, 2, 3);
  const Point3 lookAt(0, 0, 0);
  const Vec3 viewUp(0, 1, 0);
  const double distToFocus = 10;
  const double aperture = 0.1;
  Camera camera(lookFrom, lookAt, viewUp, 20.0, aspectRatio, aperture,
                distToFocus);

  // World
  const HittableList world = randomScene();

  // Render
  std::cout << "P3\n"
            << image_width << ' ' << image_height << '\n'
            << max_color << '\n';

  for (int j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      Color pixelColor(0, 0, 0);
      for (int sample = 0; sample < samplesPerPixel; ++sample) {
        const double u = (i + random_double()) / (image_width - 1);
        const double v = (j + random_double()) / (image_height - 1);
        const Ray ray = camera.getRay(u, v);
        pixelColor += rayColor(ray, world, maxDepth);
      }
      writeColor(std::cout, pixelColor, samplesPerPixel);
    }
  }
  std::cerr << "\nDone.\n";

  return 0;
}
