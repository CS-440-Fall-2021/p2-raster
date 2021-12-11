#include "../materials/Material.hpp"
#include "Geometry.hpp"

Geometry::Geometry()
{
    this->material_ptr = NULL;
}

Material *
Geometry::get_material() const
{
    return material_ptr;
}

void Geometry::set_material(Material *mPtr)
{
    if (material_ptr != nullptr)
    {
        delete this->material_ptr;
    }
    this->material_ptr = mPtr;
}

bool Geometry::shadow_hit(const Ray &ray, double &tmin) const
{
    return (false);
}