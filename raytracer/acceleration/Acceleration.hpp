#pragma once
#include "../utilities/ShadeInfo.hpp"
#include <vector>

class Ray;
class World;

class Acceleration
{
protected:
    World *world_ptr;

public:
    Acceleration(World *world_ptr);
    Acceleration() = default;
    virtual ShadeInfo hit(const Ray &ray) = 0; // compute which object a ray hits
    virtual ~Acceleration() = default;
};