#include "Image.hpp"
#include "RGBColor.hpp"
#include "../world/ViewPlane.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>

Image::Image(int hres, int vres)
{
    this->hres = hres;
    this->vres = vres;
    colors = new RGBColor *[vres];
    for (int i = 0; i < hres; i++)
    {
        colors[i] = new RGBColor[hres];
    }
}

Image::Image(const ViewPlane &vp)
{
    this->hres = vp.hres;
    this->vres = vp.vres;
    colors = new RGBColor *[vres];
    for (int i = 0; i < hres; i++)
    {
        colors[i] = new RGBColor[hres];
    }
}

Image::~Image()
{
    for (int i = 0; i < hres; i++)
    {
        delete[] colors[i];
    }
    delete[] this->colors;
}

void Image::set_pixel(int x, int y, const RGBColor &color)
{
    colors[y][x] = color;
}

void Image::write_ppm(std::string path) const
{
    float max = 0;
    for (size_t r = 0; r < this->vres; ++r)
    {
        for (size_t c = 0; c < this->hres; ++c)
        {
            max = std::max(this->colors[r][c].r,
                           std::max(this->colors[r][c].g, std::max(this->colors[r][c].b, max)));
        }
    }

    std::ofstream file;
    file.open(path);

    file << "P3" << std::endl;                // indicates PPM type
    file << hres << " " << vres << std::endl; // width and height
    file << "255" << std::endl;               // maximum value for each chanel

    double scale = 255 / max;
    for (size_t r = 0; r < vres; ++r)
    {
        for (size_t c = 0; c < hres; ++c)
        {
            file << static_cast<int>(colors[r][c].r * scale) << " "
                 << static_cast<int>(colors[r][c].g * scale) << " "
                 << static_cast<int>(colors[r][c].b * scale) << "  ";
        }
        file << std::endl;
    }
    file.close();
}