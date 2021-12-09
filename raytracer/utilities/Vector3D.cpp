#include "../utilities/Vector3D.hpp"
#include "../utilities/Point3D.hpp"
#include <cmath>
Vector3D::Vector3D()
{
   x = 0;
   y = 0;
   z = 0;
}

Vector3D::Vector3D(double c)
{
   x = c;
   y = c;
   z = c;
}

Vector3D::Vector3D(double _x, double _y, double _z)
{
   x = _x;
   y = _y;
   z = _z;
}

Vector3D::Vector3D(const Point3D &p)
{
   x = p.x;
   y = p.y;
   z = p.z;
}

Vector3D &
Vector3D::operator=(const Point3D &rhs)
{
   x = rhs.x;
   y = rhs.y;
   z = rhs.z;
   return (*this);
}

Vector3D Vector3D::operator-() const
{
   return Vector3D(-this->x, -this->y, -this->z);
}

Vector3D Vector3D::operator+(const Vector3D &v) const
{
   return Vector3D(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vector3D &Vector3D::operator+=(const Vector3D &v)
{
   x += v.x;
   y += v.y;
   z += v.z;
   return (*this);
}

Vector3D Vector3D::operator-(const Vector3D &v) const
{
   return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D Vector3D::operator-=(const Vector3D &v)
{
   x -= v.x;
   y -= v.y;
   z -= v.z;
   return (*this);
}

Vector3D Vector3D::operator*(const double a) const
{
   return Vector3D(x * a, y * a, z * a);
}

Vector3D Vector3D::operator/(const double a) const
{
   if (a != 0.0)
      return Vector3D(x / a, y / a, z / a);
   else
      return *this;
}

void Vector3D::normalize()
{
   //normalize by dividing x, y and z components by length
   double l = this->length();
   this->x /= l;
   this->y /= l;
   this->z /= l;
}

double Vector3D::length() const
{
   return (std::sqrt(this->len_squared()));
}

double Vector3D::len_squared() const
{
   return (x * x) + (y * y) + (z * z);
}

double Vector3D::operator*(const Vector3D &b) const
{
   return (x * b.x) + (y * b.y) + (z * b.z);
}

Vector3D Vector3D::operator^(const Vector3D &v) const
{
   return Vector3D((y * v.z) - (z * v.y),
                   (z * v.x) - (x * v.z),
                   (x * v.y) - (y * v.x));
}

Vector3D operator*(const double a, const Vector3D &v)
{
   return Vector3D(v.x * a, v.y * a, v.z * a);
}