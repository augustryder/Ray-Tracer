#include "camera.h"
#include "sphere.h"
#include "world.h"
#include <memory>

int main()
{
  // Add objects to world
  const auto sphere1 = std::make_shared<Sphere>(Vec3{0, 0, -3}, 1.0);
  const auto sphere2 = std::make_shared<Sphere>(Vec3{0, 1, -3}, 1.0);
  const auto ground = std::make_shared<Sphere>(Vec3{0, -100.5, -3}, 100.0);
  const World world{sphere1, sphere2, ground};

  // Setup camera and render world
  const Vec3 camera_position{0, 0, 0};
  constexpr double aspect_ratio = 16.0 / 9.0;
  constexpr int image_width = 1280;
  const Camera cam{camera_position, aspect_ratio, image_width};
  cam.render(world);
}
