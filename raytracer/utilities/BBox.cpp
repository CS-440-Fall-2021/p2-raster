#include "BBox.hpp"
#include <sstream>
#include <iostream>
#include "../geometry/Geometry.hpp"
#include "Ray.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Constants.hpp"
#include <cmath>
#include <algorithm>

BBox::BBox(const Point3D &min, const Point3D &max)
{
    pmin = min;
    pmax = max;
}

std::string BBox::to_string() const
{
    std::stringstream stream;
    stream << "pmin: " << pmin.to_string() << '\n';
    stream << "pmax: " << pmax.to_string();
    return stream.str();
}
bool BBox::hit(const Ray &ray, float &t_enter, float &t_exit) const
{
    // returns true if ray hits the BBox
    //  Reference: Ray Tracing from the Ground Up by Kevin Suffern
    float tx_max, tx_min, ty_max, ty_min, tz_max, tz_min;

    float a = 1.0 / ray.d.x;
    float b = 1.0 / ray.d.y;
    float c = 1.0 / ray.d.z;

    if (a >= 0)
    {
        tx_min = (pmin.x - ray.o.x) * a;
        tx_max = (pmax.x - ray.o.x) * a;
    }
    else
    {
        tx_min = (pmax.x - ray.o.x) * a;
        tx_max = (pmin.x - ray.o.x) * a;
    }
    if (b >= 0)
    {
        ty_min = (pmin.y - ray.o.y) * b;
        ty_max = (pmax.y - ray.o.y) * b;
    }
    else
    {
        ty_min = (pmax.y - ray.o.y) * b;
        ty_max = (pmin.y - ray.o.y) * b;
    }

    if (c >= 0)
    {
        tz_min = (pmin.z - ray.o.z) * c;
        tz_max = (pmax.z - ray.o.z) * c;
    }
    else
    {
        tz_min = (pmax.z - ray.o.z) * c;
        tz_max = (pmin.z - ray.o.z) * c;
    }
    t_enter = std::max(std::max(tx_min, ty_min), tz_min);
    t_exit = std::min(std::min(tx_max, ty_max), tz_max);
    bool val = ((t_enter < t_exit) && (t_exit > kEpsilon));
    return val;
}
bool BBox::hit(const Ray &ray) const
{
    // returns true if ray hits the BBox
    float tx_max, tx_min, ty_max, ty_min, tz_max, tz_min;

    float a = 1.0 / ray.d.x;
    float b = 1.0 / ray.d.y;
    float c = 1.0 / ray.d.z;

    if (a >= 0)
    {
        tx_min = (pmin.x - ray.o.x) * a;
        tx_max = (pmax.x - ray.o.x) * a;
    }
    else
    {
        tx_min = (pmax.x - ray.o.x) * a;
        tx_max = (pmin.x - ray.o.x) * a;
    }
    if (b >= 0)
    {
        ty_min = (pmin.y - ray.o.y) * b;
        ty_max = (pmax.y - ray.o.y) * b;
    }
    else
    {
        ty_min = (pmax.y - ray.o.y) * b;
        ty_max = (pmin.y - ray.o.y) * b;
    }

    if (c >= 0)
    {
        tz_min = (pmin.z - ray.o.z) * c;
        tz_max = (pmax.z - ray.o.z) * c;
    }
    else
    {
        tz_min = (pmax.z - ray.o.z) * c;
        tz_max = (pmin.z - ray.o.z) * c;
    }
    double t_enter, t_exit;
    t_enter = std::max(std::max(tx_min, ty_min), tz_min);
    t_exit = std::min(std::min(tx_max, ty_max), tz_max);
    bool val = ((t_enter < t_exit) && (t_exit > kEpsilon));
    return val;
}
void BBox::extend(Geometry *g)
{
    this->pmax = max(g->getBBox().pmax, pmax);
    this->pmin = min(g->getBBox().pmin, pmin);
}
void BBox::extend(const BBox &b)
{
    this->pmax = max(b.pmax, this->pmax);
    this->pmin = min(b.pmin, this->pmin);
}

bool BBox::contains(const Point3D &p)
{
    // if p is within the x, y and z bounds it is contained in the BBox
    if ((p.x > pmin.x && p.x < pmax.x) && (p.y > pmin.y && p.y < pmax.y) && (p.z > pmin.z && p.z < pmax.z))
    {
        return true;
    }
    return false;
}

bool BBox::overlaps(Geometry *g)
{
    BBox g_box = g->getBBox();

    // check if x, y and z coordinates of g and bbox overlap
    bool x_condition = (pmax.x >= g_box.pmin.x && g_box.pmax.x >= pmin.x);
    bool y_condition = (pmax.y >= g_box.pmin.y && g_box.pmax.y >= pmin.y);
    bool z_condition = (pmax.z >= g_box.pmin.z && g_box.pmax.z >= pmin.z);
    return (x_condition && y_condition && z_condition);
}
bool BBox::overlaps(const BBox &b)
{
    // check if x, y and z coordinates of b and bbox overlap
    bool x_condition = (pmax.x >= b.pmin.x && b.pmax.x >= pmin.x);
    bool y_condition = (pmax.y >= b.pmin.y && b.pmax.y >= pmin.y);
    bool z_condition = (pmax.z >= b.pmin.z && b.pmax.z >= pmin.z);
    return (x_condition && y_condition && z_condition);
}

int BBox::maximum_axis() const
{
    double x_length = pmax.x - pmin.x;
    double y_length = pmax.y - pmin.y;
    double z_length = pmax.z - pmin.z;

    if (x_length >= y_length && x_length >= z_length)
    {
        return X_AXIS;
    }

    if (y_length >= x_length && y_length >= z_length)
    {
        return Y_AXIS;
    }

    return Z_AXIS;
}