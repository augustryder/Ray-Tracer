#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "sphere.h"
#include "world.h"
#include <memory>

int main()
{
  // Define materials
  const auto red_lambertian =
      std::make_shared<Lambertian>(Color{0.8, 0.0, 0.0});
  const auto green_lambertian =
      std::make_shared<Lambertian>(Color{0.8, 0.8, 0.0});
  const auto blue_lambertian =
      std::make_shared<Lambertian>(Color{0.1, 0.2, 0.5});
  const auto silver_metal = std::make_shared<Metal>(Color{0.8, 0.8, 0.8}, 0.3);
  const auto gold_metal = std::make_shared<Metal>(Color{0.8, 0.6, 0.2}, 0.0);

  // Add objects to world
  const auto center_sphere =
      std::make_shared<Sphere>(Vec3{0, 0, -1}, 0.5, blue_lambertian);
  const auto ground =
      std::make_shared<Sphere>(Vec3{0, -100.5, -1}, 100.0, green_lambertian);
  const auto back_sphere =
      std::make_shared<Sphere>(Vec3{0.5, 0, 1}, 0.5, red_lambertian);
  const auto gold_sphere =
      std::make_shared<Sphere>(Vec3{1.1, 0, -1}, 0.5, gold_metal);
  const auto silver_sphere =
      std::make_shared<Sphere>(Vec3{-1.5, 0.3, -2}, 0.8, silver_metal);

  World world;
  world.add(ground);
  world.add(center_sphere);
  world.add(back_sphere);
  world.add(gold_sphere);
  world.add(silver_sphere);

  // Setup camera and render world
  auto camera_pos = Vec3{2, 2, 2};
  auto aspect_ratio = 16.0 / 9.0;
  auto image_width = 1280;
  auto sample_rate = 10;
  auto max_depth = 20;
  auto vertical_fov = 90.0;
  auto look_at = Vec3{0, 0, -1};
  auto roll = 20.0;

  Camera cam{camera_pos, aspect_ratio, image_width, sample_rate,
             max_depth,  vertical_fov, look_at,     roll};

  cam.render(world);
}
