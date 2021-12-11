#pragma once

/**
   Courtesy Kevin Suffern.
*/

#include "../utilities/RGBColor.hpp"
#include "../utilities/Vector3D.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Ray.hpp"

class Light
{
protected:
    RGBColor color; // the light's color.
    float ls;       // luminance
    bool shadows;   // casts shadows or not

public:
    // Constructors.
    Light();                          // set color to white (1, 1, 1).
    Light(float c);                   // set color to (c, c, c).
    Light(float r, float g, float b); // set color to (r, g, b).
    Light(const RGBColor &c);         // set color to c

    // Copy constructor and assignment operator.
    Light(const Light &rhs) = default;
    Light &operator=(const Light &rhs) = default;

    // Set color.
    void set_color(const float c);             // to (c, c, c)
    void set_color(float r, float g, float b); // to (r, g, b).
    void set_color(const RGBColor &c);         // to c.

    // Normalized direction vector from light source to hit point.
    virtual Vector3D get_direction(const ShadeInfo &s) const = 0;

    // Luminance from this light source at hit point.
    virtual RGBColor L() const = 0;

    // Destructor.
    virtual ~Light() = default;

    bool casts_shadows() const;
    virtual bool in_shadow(const Ray &ray, const ShadeInfo &si) const = 0;
};