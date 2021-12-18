#include "../utilities/Vector3D.hpp"
#include "../utilities/Point3D.hpp"
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>

Point3D::Point3D()
{
    x = 0;
    y = 0;
    z = 0;
}

Point3D::Point3D(float c)
{
    x = c;
    y = c;
    z = c;
}

Point3D::Point3D(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

std::string Point3D::to_string() const
{
    std::stringstream stream;
    stream << "(x,y,z): "
           << "(" << x << "," << y << "," << z << ")";
    return stream.str();
}

Point3D Point3D::operator-() const
{
    return Point3D(-this->x, -this->y, -this->z);
}

Vector3D Point3D::operator-(const Point3D &p) const
{
    return Vector3D(x - p.x, y - p.y, z - p.z);
}

Point3D Point3D::operator+(const Vector3D &v) const
{
    return Point3D(x + v.x, y + v.y, z + v.z);
}

Point3D Point3D::operator-(const Vector3D &v) const
{
    return Point3D(x - v.x, y - v.y, z - v.z);
}

Point3D Point3D::operator*(const float s) const
{
    return Point3D(x * s, y * s, z * s);
}

float Point3D::d_squared(const Point3D &p) const
{
    return pow(x - p.x, 2) + pow(y - p.y, 2) + pow(z - p.z, 2);
}

float Point3D::distance(const Point3D &p) const
{
    return sqrt(this->d_squared(p));
}

Point3D operator*(const float a, const Point3D &pt)
{
    return Point3D(pt.x * a, pt.y * a, pt.z * a);
}

Point3D min(const Point3D &a, const Point3D &b)
{
    return Point3D(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Point3D max(const Point3D &a, const Point3D &b)
{
    return Point3D(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

Point3D interpolate(const Point3D &a, const Point3D &b,
                    const Point3D &c, const Point3D &x,
                    const Point3D &y)
{
    return Point3D(x.x + (c.x - a.x) / (b.x - a.x) * (y.x - x.x),
                   x.y + (c.y - a.y) / (b.y - a.y) * (y.y - x.y),
                   x.z + (c.z - a.z) / (b.z - a.z) * (y.z - x.z));
}

bool Point3D::operator==(const Point3D &rhs) const
{
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}