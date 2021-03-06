/**
   This builds a simple scene that consists of a sphere, a triangle, and a
   plane.
   Parallel viewing is used with a single sample per pixel.
*/

#include "../cameras/Perspective.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"

#include "../materials/Phong.hpp"
#include "../materials/reflective.hpp"
#include "../materials/Cosine.hpp"

#include "../samplers/Simple.hpp"

#include "../utilities/Constants.hpp"

#include "../materials/matte.hpp"
#include "../samplers/Simple.hpp"

#include "../world/World.hpp"
#include "../lights/Ambient.hpp"
#include "../lights/Point.hpp"

void World::build(void)
{
  // View plane  .
  vplane.top_left.x = -10;
  vplane.top_left.y = 10;
  vplane.top_left.z = 10;
  vplane.bottom_right.x = 10;
  vplane.bottom_right.y = -10;
  vplane.bottom_right.z = 10;
  vplane.hres = 400;
  vplane.vres = 400;

  // Background color.
  bg_color = black;

  // Light Pointer
  Point *light_ptr1 = new Point;
  light_ptr1->set_position(10, 20, 10);
  light_ptr1->scale_radiance(10.0);
  light_ptr1->set_shadows(true);
  add_light(light_ptr1);

  // Material Pointers
  // Phong pointers
  Phong *pointerPH1 = new Phong;
  pointerPH1->set_cd(0, 1, 0);
  pointerPH1->set_exp(100);
  pointerPH1->set_ka(0.2);
  pointerPH1->set_kd(3);
  pointerPH1->set_ks(0.2);

  Phong *pointerPH2 = new Phong;
  pointerPH2->set_cd(1, 0, 0);
  pointerPH2->set_exp(100);
  pointerPH2->set_ka(0.2);
  pointerPH2->set_kd(3);
  pointerPH2->set_ks(0.2);

  Phong *pointerPH = new Phong;
  pointerPH->set_cd(0, 0, 1);
  pointerPH->set_exp(100);
  pointerPH->set_ka(0.2);
  pointerPH->set_kd(3);
  pointerPH->set_ks(0.2);

  // Matte pointer
  Matte *pointerMT1 = new Matte;
  pointerMT1->set_ka(0.2);
  pointerMT1->set_kd(3);
  pointerMT1->set_cd(RGBColor(0, 1, 0));

  Matte *pointerMT2 = new Matte;
  pointerMT2->set_ka(0.2);
  pointerMT2->set_kd(3);
  pointerMT2->set_cd(RGBColor(1, 0, 0));

  Matte *pointerMT3 = new Matte;
  pointerMT3->set_ka(0.2);
  pointerMT3->set_kd(3);
  pointerMT3->set_cd(RGBColor(0, 0, 1));

  // Reflective pointer
  Reflective *reflective_ptr1 = new Reflective;
  reflective_ptr1->set_ka(0.25);
  reflective_ptr1->set_kd(0.5);
  reflective_ptr1->set_cd(0, 1, 0);
  reflective_ptr1->set_ks(0.15);
  reflective_ptr1->set_exp(100.0);
  reflective_ptr1->set_kr(0.75);
  reflective_ptr1->set_cr(0.65, 1, 0.30);

  Reflective *reflective_ptr12 = new Reflective;
  reflective_ptr12->set_ka(0.25);
  reflective_ptr12->set_kd(0.5);
  reflective_ptr12->set_cd(1, 0, 0);
  reflective_ptr12->set_ks(0.15);
  reflective_ptr12->set_exp(100.0);
  reflective_ptr12->set_kr(0.75);
  reflective_ptr12->set_cr(0.65, 1, 0.30);

  // Camera and sampler.
  set_camera(new Perspective(0, 0, 20));
  sampler_ptr = new Simple(camera_ptr, &vplane);

  // sphere
  Sphere *sphere_ptr = new Sphere(Point3D(-3, 2, 0), 5);
  sphere_ptr->set_material(pointerPH1);
  add_geometry(sphere_ptr);

  // triangle
  Point3D a(2.5, -5, 1);
  Point3D b(14, -1, 0);
  Point3D c(8.5, 5, 0.5);
  Triangle *triangle_ptr = new Triangle(a, b, c);
  triangle_ptr->set_material(pointerPH2);
  add_geometry(triangle_ptr);

  // plane
  Plane *plane_ptr = new Plane(Point3D(0, 1, 0), Vector3D(0, 10, 2));
  plane_ptr->set_material(pointerPH); // green
  add_geometry(plane_ptr);
}