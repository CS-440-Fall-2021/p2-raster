#include "../cameras/Perspective.hpp"
#include "../geometry/Plane.hpp"
#include "../materials/Cosine.hpp"
#include "../materials/Phong.hpp"
#include "../materials/Matte.hpp"
#include "../samplers/Simple.hpp"
#include "../lights/Ambient.hpp"
#include "../lights/Point.hpp"
#include "../acceleration/KDTree.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"
#include "../world/World.hpp"

void World::build(void)
{
  // view plane
  vplane.top_left = Point3D(-1, 1, 2);
  vplane.bottom_right = Point3D(1, -1, 2);
  vplane.hres = 200;
  vplane.vres = 200;

  RGBColor grey(0.25);

  bg_color = grey; // background color.

  // camera and sampler.
  set_camera(new Perspective(0, 0, 10));
  sampler_ptr = new Simple(camera_ptr, &vplane);
  set_acceleration(NULL);

  Phong *pointerPH = new Phong;
  pointerPH->set_cd(0.45);
  pointerPH->set_exp(0.1);
  pointerPH->set_ka(0.2);
  pointerPH->set_kd(3);
  pointerPH->set_ks(0.2);

  // Ambient *ambient_ptr = new Ambient;
  // ambient_ptr->scale_radiance(0.5);
  // set_ambient_light(ambient_ptr);

  Point *light_ptr = new Point(RGBColor(0, 1, 0));
  light_ptr->set_shadows(true);
  light_ptr->set_position(1, -1, 1);
  light_ptr->scale_radiance(3.0);
  add_light(light_ptr);

  Point *light_ptr1 = new Point(RGBColor(1, 1, 0));
  light_ptr1->set_shadows(true);
  light_ptr1->set_position(-1, 10, 0);
  light_ptr1->scale_radiance(3.0);
  add_light(light_ptr1);

  Point *light_ptr2 = new Point(RGBColor(1, 153.0 / 255.0, 0));
  light_ptr2->set_shadows(true);
  light_ptr2->set_position(0, 50, 1);
  light_ptr2->scale_radiance(3.0);
  add_light(light_ptr2);

  Point *light_ptr3 = new Point(RGBColor(204.0 / 255.0, 0, 204.0 / 255.0));
  light_ptr3->set_shadows(true);
  light_ptr3->set_position(0.5, 100, 1);
  light_ptr3->scale_radiance(3.0);
  add_light(light_ptr3);

  Point *light_ptr4 = new Point(RGBColor(0, 0, 1));
  light_ptr4->set_shadows(true);
  light_ptr4->set_position(1, 100, 1);
  light_ptr4->scale_radiance(3.0);
  add_light(light_ptr4);

  Matte *pointerMT = new Matte;
  pointerMT->set_ka(0.2);
  pointerMT->set_kd(3);
  pointerMT->set_cd(RGBColor(0, 0, 1));

  // filename goes here
  add_ply("models/combined.ply", pointerPH, Point3D(5, -1, -3),
          Point3D(-5, 1, -1), true);
}