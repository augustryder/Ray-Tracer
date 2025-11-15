#include "camera.h"
#include "sphere.h"
#include "world.h"
#include <memory>

int main()
{
  // Add objects to world
  const auto sphere1 = std::make_shared<Sphere>(Vec3{0, 0, -1}, 0.5);
  const auto ground = std::make_shared<Sphere>(Vec3{0, -100.5, -1}, 100.0);
  const World world{sphere1, ground};

  // Setup camera and render world
  const Vec3 camera_position{0, 0, 0};
  constexpr double aspect_ratio = 16.0 / 9.0;
  constexpr int image_width = 1280;
  constexpr int samples_per_pixel = 20;
  constexpr int max_depth = 15;
  const Camera cam{camera_position, aspect_ratio, image_width,
                   samples_per_pixel, max_depth};
  cam.render(world);
}
