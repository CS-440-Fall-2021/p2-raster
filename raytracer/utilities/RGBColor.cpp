#include <cmath>
#include <sstream>
#include "../utilities/RGBColor.hpp"

RGBColor::RGBColor()
{
    r = 0.0;
    g = 0.0;
    b = 0.0;
}

RGBColor::RGBColor(float c)
{
    r = c;
    g = c;
    b = c;
}

RGBColor::RGBColor(float _r, float _g, float _b)
{
    r = _r;
    g = _g;
    b = _b;
}

RGBColor RGBColor::operator+(const RGBColor &c) const
{
    return RGBColor(r + c.r, g + c.g, b + c.b);
}

RGBColor &
RGBColor::operator+=(const RGBColor &c)
{
    r += c.r;
    g += c.g;
    b += c.b;
    return (*this);
}

RGBColor RGBColor::operator*(const float a) const
{
    return RGBColor(r * a, g * a, b * a);
}

RGBColor &
RGBColor::operator*=(const float a)
{
    r *= a;
    g *= a;
    b *= a;
    return (*this);
}

RGBColor RGBColor::operator/(const float a) const
{
    return RGBColor(r / a, g / a, b / a);
}

RGBColor &
RGBColor::operator/=(const float a)
{
    r /= a;
    g /= a;
    b /= a;
    return (*this);
}

RGBColor RGBColor::operator*(const RGBColor &c) const
{
    return RGBColor(r * c.r, g * c.g, b * c.b);
}

bool RGBColor::operator==(const RGBColor &c) const
{
    if (r == c.r && g == c.g && b == c.b)
    {
        return true;
    }
    else
    {
        return false;
    }
}

RGBColor RGBColor::powc(float p) const
{
    return (RGBColor(std::pow(r, p), std::pow(g, p), std::pow(b, p)));
}

float RGBColor::average() const
{
    return (r + g + b) / 3;
}

RGBColor operator*(const float a, const RGBColor &c)
{
    return RGBColor(a * c.r, a * c.g, a * c.b);
}
