#include <iostream>

#include "materials/Cosine.hpp"

#include "samplers/Sampler.hpp"

#include "tracers/Tracer.hpp"

#include "utilities/Image.hpp"
#include "utilities/RGBColor.hpp"
#include "utilities/Ray.hpp"
#include "utilities/ShadeInfo.hpp"

#include "world/World.hpp"
#include "world/ViewPlane.hpp"

#include "acceleration/KDtree.hpp"
#include "acceleration/BVH.hpp"

#include <chrono>
using namespace std;
using namespace std::chrono;

int main(int argc, char **argv)
{
  World world;
  world.build();

  Sampler *sampler = world.sampler_ptr;
  ViewPlane &viewplane = world.vplane;
  Image image(viewplane);
  world.set_acceleration(new BVH((&world)));
  // world.set_acceleration(new KDTree((&world)));
  auto start = high_resolution_clock::now();
  std::vector<Ray> rays;
  for (int x = 0; x < viewplane.hres; x++)
  { // across.
    for (int y = 0; y < viewplane.vres; y++)
    { // down.
      // Get rays for the pixel from the sampler. The pixel color is the
      // weighted sum of the shades for each ray.
      // if ((x % 100) == 0)
      //   fprintf(stdout, "At Pixel (%d, %d)\n",  x, y);

      RGBColor pixel_color(0);
      rays = sampler->get_rays(x, y);
      for (const auto &ray : rays)
      {
        float weight = ray.w; // ray weight for the pixel.

        pixel_color += weight * world.tracer->trace_ray(ray, 1); // TRACE RAY
      }
      // Save color to image.
      image.set_pixel(x, y, pixel_color);
      // std::cout << pixel_color << "\n";
    }
  }
  auto stop = high_resolution_clock::now();

  // Write image to file.
  image.write_ppm("scene.ppm");

  std::cout << "Wrote image.\n";

  auto duration = duration_cast<microseconds>(stop - start);

  cout << "Time taken by function: "
       << duration.count() << " microseconds" << endl;
  return 0;
}
