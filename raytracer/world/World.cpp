#include "../utilities/BBox.hpp"
#include "../cameras/Camera.hpp"
#include "../geometry/Triangle.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Plane.hpp"
#include "../samplers/Sampler.hpp"
#include "../geometry/Geometry.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../tracers/Basic.hpp"
#include "../lights/Ambient.hpp"
#include "ViewPlane.hpp"
#include "World.hpp"

#include <iostream>
#include <string>

World::World()
{
    bg_color = 0;
    camera_ptr = NULL;
    sampler_ptr = NULL;
    tracer = new Basic(this);
    ambient_ptr = new Ambient;
}

World::~World()
{
    this->camera_ptr = NULL;
    this->sampler_ptr = NULL;
    this->geometry.clear();
    delete tracer;
    delete ambient_ptr;
}

void World::add_geometry(Geometry *geom_ptr)
{
    geometry.push_back(geom_ptr);
}

void World::set_camera(Camera *c_ptr)
{
    this->camera_ptr = c_ptr;
}

ShadeInfo World::hit_objects(const Ray &ray)
{

    ShadeInfo shadeInfo(*this);
    ShadeInfo shadeInfoMin(*this);
    float t;
    float tmin = kHugeValue;

    for (int i = 0; i < geometry.size(); i++)
    {
        if (geometry[i]->hit(ray, t, shadeInfo) && (t < tmin))
        {
            tmin = t;

            shadeInfoMin = shadeInfo;
            shadeInfoMin.hit = true;
            shadeInfoMin.material_ptr = geometry[i]->get_material();
            shadeInfoMin.ray = ray;
            shadeInfoMin.t = t;
        }
    }
    return shadeInfoMin;
}

void World::set_ambient_light(Ambient *amb_ptr)
{
    if (ambient_ptr)
    {
        delete ambient_ptr;
    }
    ambient_ptr = amb_ptr->clone();
}
