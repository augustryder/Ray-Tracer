#include "camera.h"
#include "dielectric.h"
#include "lambertian.h"
#include "metal.h"
#include "sphere.h"
#include "vec3.h"
#include "world.h"
#include <memory>

int main()
{
  World world;
  const auto ground_material =
      std::make_shared<Lambertian>(Color{0.5, 0.5, 0.5});
  const auto ground =
      std::make_shared<Sphere>(Vec3{0, -1000, 0}, 1000.0, ground_material);
  world.add(ground);

  for (int a = -5; a < 5; a++)
  {
    for (int b = -5; b < 5; b++)
    {
      auto choose_mat = random_double();
      Vec3 center{a + 0.9 * random_double(), 0.2, b + 0.9 * random_double()};

      if ((center - Vec3(4, 0.2, 0)).length() > 0.9)
      {
        std::shared_ptr<Material> sphere_material;
        if (choose_mat < 0.8)
        {
          // diffuse
          auto albedo = random_vector();
          sphere_material = std::make_shared<Lambertian>(albedo);
          world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
        }
        else if (choose_mat < 0.95)
        {
          // metal
          auto albedo = random_vector(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          sphere_material = std::make_shared<Metal>(albedo, fuzz);
          world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
        }
        else
        {
          // glass
          sphere_material = std::make_shared<Dielectric>(1.5);
          world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = std::make_shared<Dielectric>(1.0 / 1.5);
  world.add(make_shared<Sphere>(Vec3(0, 1, 0), 1.0, material1));
  auto material2 = std::make_shared<Lambertian>(Vec3(0.4, 0.2, 0.1));
  world.add(make_shared<Sphere>(Vec3(-4, 1, 0), 1.0, material2));
  auto material3 = std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
  world.add(make_shared<Sphere>(Vec3(4, 1, 0), 1.0, material3));

  // Setup camera and render
  auto aspect_ratio = 16.0 / 9.0;
  auto image_width = 1920;
  auto sample_rate = 100;
  auto max_depth = 50;
  auto vertical_fov = 20.0;
  auto look_from = Vec3{13, 2, 3};
  auto look_at = Vec3{0, 0, 0};
  auto roll = 0.0;
  auto defocus_angle = 0.4;
  auto focus_distance = 10.0;

  Camera cam{look_from,     aspect_ratio,  image_width, sample_rate,
             max_depth,     vertical_fov,  look_at,     roll,
             defocus_angle, focus_distance};

  cam.render(world);
}
