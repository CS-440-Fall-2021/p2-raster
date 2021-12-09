#include "Ray.hpp"
#include <sstream>

Ray::Ray()
{
    o = Point3D(0.0, 0.0, 0.0);
    d = Vector3D(0.0, 0.0, 1.0);
    w = 1.0;
}
Ray::Ray(const Point3D &origin, const Vector3D &dir)
{
    o = origin;
    d = dir;
    w = 1.0;
}

std::string Ray::to_string() const
{
    std::stringstream stream;
    stream << "Origin Point: (" << o.x << "," << o.y << "," << o.z << ")" << '\n';
    stream << "Direction Vector: (" << d.x << "," << d.y << "," << d.z << ")";
    return stream.str();
}