#include "Light.hpp"

Light::Light()
{
    color = RGBColor(1);
    ls = 1.0;
    shadows = false;
}
Light::Light(float c)
{
    color = RGBColor(c);
    ls = 1.0;
    shadows = false;
}
Light::Light(float r, float g, float b)
{
    color = RGBColor(r, g, b);
    ls = 1.0;
    shadows = false;
}
Light::Light(const RGBColor &c)
{
    color = c;
    ls = 1.0;
    shadows = false;
}

void Light::set_color(float c)
{
    color = RGBColor(c);
}

void Light::set_color(float r, float g, float b)
{
    color = RGBColor(r, g, b);
}

void Light::set_color(const RGBColor &c)
{
    color = c;
}

bool Light::casts_shadows() const
{
    return shadows;
}
