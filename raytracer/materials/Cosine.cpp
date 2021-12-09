#include "Cosine.hpp"
#include "../utilities/ShadeInfo.hpp"

Cosine::Cosine()
{
    color = RGBColor(0);
}

Cosine::Cosine(float c)
{
    color = RGBColor(c);
}

Cosine::Cosine(float r, float g, float b)
{
    color = RGBColor(r, g, b);
}

Cosine::Cosine(const RGBColor &c)
{
    color = c;
}

Cosine::Cosine(const Cosine &other)
{
    color = RGBColor(other.color.r, other.color.g, other.color.b);
}

Cosine &Cosine::operator=(const Cosine &other)
{
    if (this == &other)
        return (*this);

    Cosine::operator=(other);
    color.r = other.color.r;
    color.g = other.color.g;
    color.b = other.color.b;
    return (*this);
}

RGBColor Cosine::shade(const ShadeInfo &sinfo) const
{
    return this->color * (sinfo.normal * -sinfo.ray.d);
}