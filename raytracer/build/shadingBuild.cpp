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
  vplane.hres = 500;
  vplane.vres = 500;
  // acceleration_ptr = new KDTree(this);

  // set isSmooth as true for smooth shading & false for flat shading
  bool isSmooth = true;

  RGBColor grey(0.25);
  RGBColor lightPurple(0.65, 0.3, 1); // light purple
  RGBColor lightGreen(0.65, 1, 0.30); // light green

  bg_color = lightGreen;       // background color.
  RGBColor orange(1, 0.75, 0); // orange
  // camera and sampler.
  set_camera(new Perspective(0, 0, 10));
  sampler_ptr = new Simple(camera_ptr, &vplane);
  set_acceleration(NULL);

  // Lighting
  Point *light_ptr = new Point;
  light_ptr->set_position(50, 50, 50);
  light_ptr->scale_radiance(3.0);
  light_ptr->set_shadows(true);
  add_light(light_ptr);

  Phong *pointerPH = new Phong;
  pointerPH->set_cd(1);
  pointerPH->set_exp(0.1);
  pointerPH->set_ka(0.2);
  pointerPH->set_kd(3);
  pointerPH->set_ks(0.2);

  // Ambient *ambient_ptr = new Ambient;
  // ambient_ptr->scale_radiance(0.5);
  // set_ambient_light(ambient_ptr);

  Matte *pointerMT = new Matte;
  pointerMT->set_ka(0.2);
  pointerMT->set_kd(3);
  pointerMT->set_cd(RGBColor(0, 0, 1));

  Plane *plane_ptr = new Plane(Point3D(0, -1, 0), Vector3D(0, 10, 2));
  plane_ptr->set_material(pointerMT);

  // add_geometry(plane_ptr);

  // filename goes here
  add_ply("models/bun_zipper_res4.ply", pointerPH, Point3D(1, -1, -1),
          Point3D(-1, 1, -3), isSmooth);
}