#include "Whitted.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"
#include "../materials/Material.hpp"



Whitted::Whitted(): Tracer() {};

Whitted::Whitted(World *w_ptr): Tracer(w_ptr) {};

RGBColor Whitted::trace_ray(const Ray &ray, const int depth) const
{
    float weight = ray.w;
    ShadeInfo sinfo = world_ptr->hit_objects(ray);
    
    if (sinfo.hit) 
    {
        sinfo.ray = ray;
        sinfo.depth = depth;
        
        return sinfo.material_ptr->shade(sinfo); // CHANGE THE SHADING FUNCTION CALLED HERE
    }
    else
    {
        return world_ptr->bg_color;
    }
}