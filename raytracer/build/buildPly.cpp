#include "../cameras/Perspective.hpp"
#include "../geometry/Plane.hpp"
#include "../materials/Cosine.hpp"
#include "../materials/Phong.hpp"
#include "../materials/Matte.hpp"
#include "../samplers/Simple.hpp"
#include "../lights/Ambient.hpp"
#include "../lights/Point.hpp"

#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"
#include "../world/World.hpp"

void World::build(void) {
  // view plane
  vplane.top_left = Point3D(-1, 1, 2);
  vplane.bottom_right = Point3D(1, -1, 2);
  vplane.hres = 800;
  vplane.vres = 800;

  RGBColor grey(0.25);

  bg_color = grey;  // background color.

  // camera and sampler.
  set_camera(new Perspective(0, 0, 10));
  sampler_ptr = new Simple(camera_ptr, &vplane);

  Phong *pointerPH = new Phong;
  pointerPH->set_cd(0.45);
  pointerPH->set_exp(0.1);
  pointerPH->set_ka(0.2);
  pointerPH->set_kd(3);
  pointerPH->set_ks(0.2);

  // Ambient *ambient_ptr = new Ambient;
  // ambient_ptr->scale_radiance(0.5);
  // set_ambient_light(ambient_ptr);

  Point *light_ptr = new Point;
  light_ptr->set_position(1, 1, 1);
  light_ptr->scale_radiance(3.0);
  add_light(light_ptr);

  // Matte *pointerPH = new Matte;
  // pointerPH->set_ka(0.2);
  // pointerPH->set_kd(3);
  // pointerPH->set_cd(RGBColor(0,0,1));

  // filename goes here
  add_ply("models/knight.ply", pointerPH, Point3D(-1, -1, -1),
          Point3D(1, 1, 1), true);
}
