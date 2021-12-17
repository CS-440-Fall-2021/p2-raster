#include "../utilities/BBox.hpp"
#include "../cameras/Camera.hpp"
#include "../geometry/Triangle.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Plane.hpp"
#include "../samplers/Sampler.hpp"
#include "../geometry/Geometry.hpp"
#include "../geometry/SmoothTriangle.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../tracers/Basic.hpp"
#include "../lights/Ambient.hpp"
#include "../acceleration/Acceleration.hpp"
#include "../acceleration/KDTree.hpp"
#include "../happly/happly.h"
#include "ViewPlane.hpp"
#include "World.hpp"
#include "../materials/Material.hpp"

#include <iostream>
#include <string>
#include <array>

World::World()
{
    bg_color = 0;
    camera_ptr = NULL;
    sampler_ptr = NULL;
    tracer = new Basic(this);
    ambient_ptr = new Ambient;
    acceleration_ptr = new KDTree(this);
    // tracer = NULL;
}

World::~World()
{
    this->camera_ptr = NULL;
    this->sampler_ptr = NULL;
    this->geometry.clear();
    this->lights.clear();
    delete tracer;
    delete ambient_ptr;
    delete acceleration_ptr;
    delete sampler_ptr;
    delete camera_ptr;
}

void World::set_tracer(Tracer *t_ptr)
{
    tracer = t_ptr;
}

void World::add_geometry(Geometry *geom_ptr)
{
    geometry.push_back(geom_ptr);
}

void World::add_light(Light *light_ptr)
{
    lights.push_back(light_ptr);
}

void World::set_camera(Camera *c_ptr)
{
    this->camera_ptr = c_ptr;
}

ShadeInfo World::hit_objects(const Ray &ray)
{
    if (acceleration_ptr != NULL)
    {
        // fprintf(stdout, "At Pixel");
        return acceleration_ptr->hit_objects(ray);
    }

    ShadeInfo shadeInfo(*this);
    ShadeInfo shadeInfoMin(*this);
    float t;
    float tmin = kHugeValue;

    for (int i = 0; i < geometry.size(); i++)
    {
        if (geometry[i]->hit(ray, t, shadeInfo) && (t < tmin))
        {
            tmin = t;

            shadeInfoMin = shadeInfo;
            shadeInfoMin.hit = true;
            shadeInfoMin.material_ptr = geometry[i]->get_material();
            shadeInfoMin.ray = ray;
            shadeInfoMin.t = t;
        }
    }
    return shadeInfoMin;
}

void World::set_ambient_light(Ambient *amb_ptr)
{
    if (ambient_ptr)
    {
        delete ambient_ptr;
    }
    ambient_ptr = amb_ptr->clone();
}

void World::add_ply(std::string fname, Material *mPtr, Point3D bottom,
                    Point3D top, bool makeSmooth)
{
    // Construct the data object by reading from file
    happly::PLYData plyIn(fname);

    // Get mesh-style data from the object
    std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
    std::vector<std::vector<size_t>> fInd = plyIn.getFaceIndices<size_t>();
    std::vector<Point3D> points;
    std::vector<Vector3D> normals;
    Vector3D normal;

    Point3D modelMin = Point3D(vPos[0][0], vPos[0][1], vPos[0][2]);
    Point3D modelMax = Point3D(vPos[0][0], vPos[0][1], vPos[0][2]);

    for (const std::array<double, 3> &point : vPos)
    {
        points.push_back(Point3D(point[0], point[1], point[2]));
        modelMin = min(modelMin, Point3D(point[0], point[1], point[2]));
        modelMax = max(modelMax, Point3D(point[0], point[1], point[2]));
    }

    for (Point3D &point : points)
    {
        point = interpolate(modelMin, modelMax, point, bottom, top);
    }

    // prepare normals array
    if (makeSmooth)
    {
        normals.resize(vPos.size());
    }

    // loop through faces
    for (std::vector<size_t> face : fInd)
    {
        if (makeSmooth)
        {
            // calculate normals
            normal = ((points[face[1]] - points[face[0]]) ^
                      (points[face[2]] - points[face[0]]));
            normal.normalize();
            for (size_t vIndex : face)
            {
                normals[vIndex] += normal;
            }
        }
        else
        {
            Triangle *fTriangle =
                new Triangle(points[face[0]], points[face[1]], points[face[2]]);
            fTriangle->set_material(mPtr->clone());
            add_geometry(fTriangle);
        }
    }

    if (makeSmooth)
    {
        for (size_t n = 0; n < normals.size(); ++n)
        {
            normals[n].normalize();
        }
        // add smooth triangles
        for (std::vector<size_t> face : fInd)
        {
            SmoothTriangle *fSTriangle = new SmoothTriangle(
                points[face[0]], points[face[1]], points[face[2]], normals[face[0]],
                normals[face[1]], normals[face[2]]);
            fSTriangle->set_material(mPtr->clone());
            add_geometry(fSTriangle);
        }
    }

    delete mPtr;
}

void World::set_acceleration(Acceleration *_acceleration_ptr)
{
    acceleration_ptr = _acceleration_ptr;
}