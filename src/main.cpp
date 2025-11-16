#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "sphere.h"
#include "world.h"
#include <memory>

int main()
{
  // Materials
  const auto lamb_mat = std::make_shared<Lambertian>(Color{0.5, 0.8, 0.5});
  const auto metal_mat = std::make_shared<Metal>(Color{0.8, 0.3, 0.5});
  // Add objects to world
  const auto sphere1 = std::make_shared<Sphere>(Vec3{0, 0, -1}, 0.5, metal_mat);
  const auto ground =
      std::make_shared<Sphere>(Vec3{0, -100.5, -1}, 100.0, lamb_mat);
  const auto back_sphere =
      std::make_shared<Sphere>(Vec3{0.5, 0, 1}, 0.5, lamb_mat);
  const World world{sphere1, ground, back_sphere};

  // Setup camera and render world
  const Vec3 camera_position{0, 0, 0};
  constexpr double aspect_ratio = 16.0 / 9.0;
  constexpr int image_width = 1280;
  constexpr int samples_per_pixel = 8;
  constexpr int max_depth = 20;
  const Camera cam{camera_position, aspect_ratio, image_width,
                   samples_per_pixel, max_depth};
  cam.render(world);
}
