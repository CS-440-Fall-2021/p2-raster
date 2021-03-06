#include "SmoothTriangle.hpp"
#include <algorithm>
#include "../utilities/Constants.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/BBox.hpp"
#include <sstream>

SmoothTriangle::SmoothTriangle() : n0{0, 0, 1}, n1{0, 0, 1}, n2{0, 0, 1} {}

SmoothTriangle::SmoothTriangle(const Point3D &a, const Point3D &b,
                               const Point3D &c, const Vector3D &na,
                               const Vector3D &nb, const Vector3D &nc)
    : v0{a}, v1{b}, v2{c}, n0{na}, n1{nb}, n2{nc} {}

SmoothTriangle *SmoothTriangle::clone() const
{
  return new SmoothTriangle(*this);
}

bool SmoothTriangle::hit(const Ray &ray, float &t_, ShadeInfo &sinfo) const
{
  // Taken from Suffern 479
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

  // Update ShadeInfo contents
  sinfo.hit = true;
  sinfo.material_ptr = this->get_material();
  sinfo.hit_point = ray.o + (t * ray.d);
  sinfo.normal = interpolate_normal(beta, gamma);
  sinfo.ray = ray;
  sinfo.t = t;
  t_ = t;

  return true;
}

Vector3D SmoothTriangle::interpolate_normal(const double beta,
                                            const double gamma) const
{
  Vector3D normal((1 - beta - gamma) * n0 + beta * n1 + gamma * n2);
  normal.normalize();

  return normal;
}

BBox SmoothTriangle::getBBox() const
{
  Point3D globalmax = max(max(v0, v1), v2);
  Point3D globalmin = min(min(v0, v1), v2);
  return BBox(globalmin, globalmax);
}
std::string SmoothTriangle::to_string() const
{
  std::stringstream stream;
  stream << "Point v0: (" << v0.x << "," << v0.y << "," << v0.z << ")" << '\n';
  stream << "Point v1: (" << v1.x << "," << v1.y << "," << v1.z << ")";
  stream << "Point v2: (" << v2.x << "," << v2.y << "," << v2.z << ")";
  return stream.str();
}

Point3D SmoothTriangle::getCenter() const
{
  Point3D centroid((v0.x + v1.x + v2.x) / 3, (v0.y + v1.y + v2.y) / 3, (v0.z + v1.z + v2.z) / 3);
  return centroid;
}