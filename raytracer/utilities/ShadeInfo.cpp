#include "ShadeInfo.hpp"
#include "Vector3D.hpp"
#include "../world/World.hpp"
#include "Constants.hpp"

ShadeInfo::ShadeInfo(const World &wr)
{
    w = &wr;
    hit = false;
    material_ptr = NULL;
    hit_point = Point3D();
    normal = Vector3D();
    ray = Ray();
    depth = 0;
    t = 0;
}