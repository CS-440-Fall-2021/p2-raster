#include "Parallel.hpp"

Parallel::Parallel()
{
    dir.x = 0;
    dir.y = 0;
    dir.z = -1;
}

Parallel::Parallel(float c)
{
    dir.x = c;
    dir.y = c;
    dir.z = c;
    dir.normalize();
}

Parallel::Parallel(float x, float y, float z)
{
    dir.x = x;
    dir.y = y;
    dir.z = z;
    dir.normalize();
}

Parallel::Parallel(const Vector3D &d)
{
    dir.x = d.x;
    dir.y = d.y;
    dir.z = d.z;
    dir.normalize();
}

Parallel::Parallel(const Parallel &camera)
{
    this->dir = camera.dir;
}

Parallel &Parallel::operator=(const Parallel &other)
{
    if (this == &other)
        return (*this);

    dir = other.dir;
    return *this;
}

Vector3D Parallel::get_direction(const Point3D &p) const
{
    return this->dir;
}