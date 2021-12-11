
#include "Plane.hpp"
#include <sstream>
#include "../utilities/Ray.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/BBox.hpp"

Plane::Plane()
{
    a = Point3D(0, 0, 0);
    n = Vector3D(0, 0, 1);
}
Plane::Plane(const Point3D &pt, const Vector3D &n)
{
    a = pt;
    this->n = n;
    this->n.normalize();
}
Plane::Plane(const Plane &object)
{
    a = object.a;
    n = object.n;
}
Plane &Plane::operator=(const Plane &rhs)
{
    if (this == &rhs)
        return (*this);

    Geometry::operator=(rhs);

    a = rhs.a;
    n = rhs.n;
    return (*this);
}
std::string Plane::to_string() const
{
    std::stringstream stream;
    stream << "Point a: (" << a.x << "," << a.y << "," << a.z << ")" << '\n';
    stream << "Normal n: (" << n.x << "," << n.y << "," << n.z << ")";
    return stream.str();
}
bool Plane::hit(const Ray &ray, float &t, ShadeInfo &s) const
{
    // returns true if ray hits the plane
    //  Reference: Ray Tracing from the Ground Up by Kevin Suffern

    float t_new = ((a - ray.o) * n) / (ray.d * n);
    if (t_new > kEpsilon)
    {
        t = t_new;
        s.hit_point = ray.o + (t * ray.d);
        s.normal = n;
        s.normal.normalize();
        return true;
    }
    return false;
}
bool Plane::shadow_hit(const Ray &ray, double &tmin) const
{
    float t = (a - ray.o) * n / (ray.d * n);

    if (t > kEpsilon)
    {
        tmin = t;
        return (true);
    }
    else
        return (false);
}

BBox Plane::getBBox() const
{
    BBox bbox;
    return bbox;
}