#include "Basic.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"
#include "../materials/Material.hpp"



Basic::Basic(): Tracer() {};

Basic::Basic(World *w_ptr): Tracer(w_ptr) {};

RGBColor Basic::trace_ray(const Ray &ray, const int depth) const
{
    if (depth > 1)
    {
        return black;
    }
    else
    {
        float weight = ray.w;
        ShadeInfo sinfo = world_ptr->hit_objects(ray);
        
        if (sinfo.hit) 
        {
            sinfo.ray = ray;
            sinfo.depth = depth;
            
            return sinfo.material_ptr->shade(sinfo);
        }
        else
        {
            return world_ptr->bg_color;
        }
    }
}