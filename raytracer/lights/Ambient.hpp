#include "../utilities/ShadeInfo.hpp"
#include "Light.hpp"

/**
   Courtesy Kevin Suffern.
*/

class Ambient : public Light
{
public:
    // Constructors.
    Ambient();                          // set color to white (1, 1, 1).
    Ambient(float c);                   // set color to (c, c, c).
    Ambient(float r, float g, float b); // set color to (r, g, b).
    Ambient(const RGBColor &c);         // set color to c.

    // Copy constructor and assignment operator.
    Ambient(const Ambient &rhs) = default;
    Ambient &operator=(const Ambient &rhs) = default;

    // Virtual copy constructor
    Ambient *clone() const;

    virtual Vector3D get_direction(const ShadeInfo &s) const override;
    virtual RGBColor L() const override;
    void scale_radiance(const float b);

    // Destructor.
    virtual ~Ambient() = default;
    virtual bool in_shadow(const Ray &ray, const ShadeInfo &si) const override;
};