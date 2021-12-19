#include "ViewPlane.hpp"

ViewPlane::ViewPlane()
{
    this->top_left = Point3D(-320, 240, 0); //x: -hres/2, y: vres/2
    this->bottom_right = Point3D(320, -240, 0);  //x: hres/2, y: -vres/2
    this->normal = Vector3D(-320, 240, 0) ^ Vector3D(320, -240, 0);
    this->hres = 640;
    this->vres = 240;
    this->max_depth = 1;
}

int ViewPlane::get_hres() const
{
    return this->hres;
}

int ViewPlane::get_vres() const
{
    return this->vres;
}

void ViewPlane::set_hres(int a)
{
    hres = a;
}

void ViewPlane::set_vres(int a)
{
    vres = a;
}

void ViewPlane::set_max_depth(int a)
{
    max_depth = a;
}