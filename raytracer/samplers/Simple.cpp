#include <iostream>
#include "../utilities/Ray.hpp"
#include "../cameras/Camera.hpp"
#include "../world/ViewPlane.hpp"
#include "Simple.hpp"

Simple::Simple(Camera *c_ptr, ViewPlane *v_ptr)
{
    this->camera_ptr = c_ptr;
    this->viewplane_ptr = v_ptr;
}

Simple::Simple(const Simple &camera)
{
    this->camera_ptr = camera.camera_ptr;
    this->viewplane_ptr = camera.viewplane_ptr;
}

Simple &Simple::operator=(const Simple &other)
{
    if (this == &other)
        return (*this);

    this->camera_ptr = other.camera_ptr;
    this->viewplane_ptr = other.viewplane_ptr;
    return (*this);
}

std::vector<Ray> Simple::get_rays(int px, int py) const
{
    //get ray shooting through pixel (px,py)

    std::vector<Ray> rays; //array of all rays
    Ray r;
    Point3D origin;

    //get vector diagonally across plane
    Vector3D dif = viewplane_ptr->bottom_right - viewplane_ptr->top_left;

    double d_X = (double)px / (double)(viewplane_ptr->hres); // subdivisions of x
    double d_Y = (double)py / (double)(viewplane_ptr->vres); // subdivisions of y

    // set origin
    origin = viewplane_ptr->top_left + Vector3D(d_X * dif.x, d_Y * dif.y, 0);

    r.o = origin;
    r.d = camera_ptr->get_direction(origin);
    r.d.normalize();

    rays.push_back(r);
    return rays;
}
