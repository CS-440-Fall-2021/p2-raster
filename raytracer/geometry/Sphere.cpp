#include "Sphere.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/ShadeInfo.hpp"
#include <cmath>
#include <sstream>
#include <sstream>

Sphere::Sphere()
{
    c = Point3D(0, 0, 0);
    r = 0;
}
Sphere::Sphere(const Point3D &center, float radius)
{
    c = center;
    r = radius;
}
Sphere::Sphere(const Sphere &object)
{
    c = object.c;
    r = object.r;
}
Sphere &Sphere::operator=(const Sphere &rhs)
{
    if (this == &rhs)
        return (*this);
    Geometry::operator=(rhs);
    c = rhs.c;
    r = rhs.r;
    return (*this);
}
std::string Sphere::to_string() const
{
    std::stringstream stream;
    stream << "Center: " << c.x << "," << c.y << "," << c.z << ")" << '\n';
    stream << "Radius: " << r;

    return stream.str();
}
bool Sphere::hit(const Ray &ray, float &t, ShadeInfo &s) const
{
    // returns true if ray hits the sphere
    //  Reference: Ray Tracing from the Ground Up by Kevin Suffern
    double t_;
    Vector3D temp = ray.o - c;
    double a = ray.d * ray.d;
    double b = 2 * ray.d * temp;
    double c_ = (temp * temp) - (r * r);
    double disc = (b * b) - (4 * a * c_); // discriminant
    if (disc < 0)
    {
        return false; // no intersection
    }
    else
    {
        double e = std::sqrt(disc);
        double denom = 2 * a;
        t_ = (-b - e) / denom;
        if (t_ > kEpsilon)
        {
            t = t_;
            s.normal = (temp + t * ray.d) / r;
            s.hit_point = ray.o + (t_ * ray.d);
            s.normal.normalize();
            return true;
        }
        t_ = (-b + e) / denom;
        if (t > kEpsilon)
        {
            t = t_;
            s.normal = (temp + t * ray.d) / r;
            s.normal.normalize();
            s.hit_point = ray.o + t * ray.d;
            return true;
        }
    }
    return false;
}

bool Sphere::shadow_hit(const Ray &ray, double &tmin) const
{
    double t;
    Vector3D temp = ray.o - c;
    double a = ray.d * ray.d;
    double b = 2.0 * temp * ray.d;
    double c = temp * temp - r * r;
    double disc = b * b - 4.0 * a * c;

    if (disc < 0.0)
        return (false);
    else
    {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom; // smaller root

        if (t > kEpsilon)
        {
            tmin = t;
            return (true);
        }

        t = (-b + e) / denom; // larger root

        if (t > kEpsilon)
        {
            tmin = t;
            return (true);
        }
    }

    return (false);
}
BBox Sphere::getBBox() const // returns a bounding box for the sphere
{
    return BBox(Point3D(c.x - r, c.y - r, c.z - r), Point3D(c.x + r, c.y + r, c.z + r));
}

Point3D Sphere::getCenter() const
{
    return c;
}