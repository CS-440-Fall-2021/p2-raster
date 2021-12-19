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

#include "../samplers/Simple.hpp"

#include "../utilities/Constants.hpp"

#include "../materials/Matte.hpp"
#include "../samplers/Simple.hpp"

#include "../world/World.hpp"
#include "../lights/Ambient.hpp"
#include "../lights/Point.hpp"
#include "../lights/Directional.hpp"

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

    // Camera and sampler.
    set_camera(new Perspective(0, 0, 20));
    sampler_ptr = new Simple(camera_ptr, &vplane);

    // Material Pointers
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

    // Lighting
    Ambient *ambient_ptr = new Ambient(1.0);
    ambient_ptr->scale_radiance(0.5);
    set_ambient_light(ambient_ptr);

    Point *light_ptr = new Point;
    light_ptr->set_position(10, 20, 10);
    light_ptr->scale_radiance(10.0);
    light_ptr->set_shadows(true);
    add_light(light_ptr);

    Point *light_ptr1 = new Point;
    light_ptr1->set_position(10, -10, 10);
    light_ptr1->scale_radiance(10.0);
    light_ptr1->set_shadows(true);
    add_light(light_ptr1);

    Directional *dir_ptr = new Directional;
    dir_ptr->set_direction(50, 50, 0);
    dir_ptr->set_color(RGBColor(1, 1, 1));
    add_light(dir_ptr);

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