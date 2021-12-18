#include "Triangle.hpp"
#include <sstream>
#include "../utilities/Point3D.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/BBox.hpp"

/**
   Courtesy Kevin Suffern.
*/

Triangle::Triangle()
{
    v0 = Point3D();
    v1 = Point3D();
    v2 = Point3D();
}
Triangle::Triangle(const Point3D &p1, const Point3D &p2, const Point3D &p3)
{
    v0 = p1;
    v1 = p2;
    v2 = p3;
}
Triangle::Triangle(const Triangle &object)
{
    v0 = object.v0;
    v1 = object.v1;
    v2 = object.v2;
}
Triangle &Triangle::operator=(const Triangle &rhs)
{
    if (this == &rhs)
        return (*this);
    Geometry::operator=(rhs);
    v0 = rhs.v0;
    v1 = rhs.v1;
    v2 = rhs.v2;
    return (*this);
}
std::string Triangle::to_string() const
{
    std::stringstream stream;
    stream << "Point v0: (" << v0.x << "," << v0.y << "," << v0.z << ")" << '\n';
    stream << "Point v1: (" << v1.x << "," << v1.y << "," << v1.z << ")";
    stream << "Point v2: (" << v2.x << "," << v2.y << "," << v2.z << ")";
    return stream.str();
}
bool Triangle::hit(const Ray &ray, float &t, ShadeInfo &s) const
{
    // returns true if ray hits the triangle
    //  Reference: Ray Tracing from the Ground Up by Kevin Suffern
    float a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
    float e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
    float i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

    double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
    double q = g * i - e * k, s_ = e * j - f * i;

    float inv_denom = 1.0 / (a * m + b * q + c * s_);

    double e1 = d * m - b * n - c * p;
    double beta = e1 * inv_denom;

    if (beta < 0.0)
        return (false);

    double r = e * l - h * i;
    double e2 = a * n + d * q + c * r;
    double gamma = e2 * inv_denom;

    if (gamma < 0.0)
        return (false);

    if (beta + gamma > 1.0)
        return (false);

    double e3 = a * p - b * r + d * s_;
    double t_ = e3 * inv_denom;

    if (t_ < kEpsilon)
        return (false);

    // t = t_;

    // updating s
    // s.hit_point = ray.o + (t * ray.d);
    // s.normal = ;
    // s.normal.normalize();

    s.hit = true;
    s.material_ptr = this->get_material();
    s.hit_point = ray.o + (t_ * ray.d);
    s.normal = (v1 - v0) ^ (v2 - v0);
    s.normal.normalize();
    s.ray = ray;
    s.t = t_;
    t = t_;
    return (true);
}
bool Triangle::shadow_hit(const Ray &ray, double &tmin) const
{
    double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x;
    double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
    double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;

    double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
    double q = g * i - e * k, s = e * j - f * i;

    double inv_denom = 1.0 / (a * m + b * q + c * s);

    double e1 = d * m - b * n - c * p;
    double beta = e1 * inv_denom;

    if (beta < 0.0)
        return (false);

    double r = e * l - h * i;
    double e2 = a * n + d * q + c * r;
    double gamma = e2 * inv_denom;

    if (gamma < 0.0)
        return (false);

    if (beta + gamma > 1.0)
        return (false);

    double e3 = a * p - b * r + d * s;
    double t = e3 * inv_denom;

    if (t < kEpsilon)
        return (false);

    tmin = t;

    return (true);
}

BBox Triangle::getBBox() const
{
    // get the least and max coordinates for bounding box
    return BBox(min(min(v0, v1), v2), max(max(v0, v1), v2));
}

Point3D Triangle::getCenter() const
{
    Point3D centroid((v0.x + v1.x + v2.x) / 3, (v0.y + v1.y + v2.y) / 3, (v0.z + v1.z + v2.z) / 3);
    return centroid;
}