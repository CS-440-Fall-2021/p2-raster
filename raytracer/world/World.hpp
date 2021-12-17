#pragma once

/**
   This file declares the World class which contains all the information about
   the scene - geometry and materials, lights, viewplane, camera, samplers, and
   acceleration structures.

   It also traces rays through the scene.

   Courtesy Kevin Suffern.
*/

#include <vector>

#include "../utilities/RGBColor.hpp"

#include "ViewPlane.hpp"

class Camera;
class Geometry;
class Ray;
class Sampler;
class ShadeInfo;
class Tracer;
class Light;
class Ambient;
class Acceleration;

class World
{
public:
  ViewPlane vplane;
  RGBColor bg_color;
  std::vector<Geometry *> geometry;
  std::vector<Light *> lights;
  Camera *camera_ptr;
  Sampler *sampler_ptr;
  Tracer *tracer;
  Light *ambient_ptr;
  Acceleration *acceleration_ptr;

public:
  // Constructors.
  World(); // initialize members.

  // Destructor.
  ~World(); // free memory.

  // Add to the scene.
  void add_geometry(Geometry *geom_ptr);
  void set_camera(Camera *c_ptr);
  void set_ambient_light(Ambient *amb_ptr);
  void add_light(Light *light_ptr);
  void set_tracer(Tracer *t_ptr);
  void set_acceleration(Acceleration *acceleration_ptr);

  // void set_ambient_light(Ambient *amb_ptr);

  // Build scene - add all geometry, materials, lights, viewplane, camera,
  // samplers, and acceleration structures
  void build();

  // Returns appropriate shading information corresponding to intersection of
  // the ray with the scene geometry.
  ShadeInfo hit_objects(const Ray &ray);

  void add_ply(std::string fname, Material *mPtr, Point3D bottom,
               Point3D top, bool makeSmooth);
};
