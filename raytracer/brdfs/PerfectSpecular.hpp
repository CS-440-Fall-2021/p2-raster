#pragma once

#include "BRDF.hpp"

/*

   Courtesy Kevin Suffern.

*/

class PerfectSpecular: public BRDF
{
    private:
        float kr;
        RGBColor cr;

    public:
        // Constructor.
        PerfectSpecular();

        // Copy constructor.
        PerfectSpecular(const PerfectSpecular &ps);

        // Virtual copy constructor.
        virtual PerfectSpecular *clone() const;

        // Destructor.
        virtual ~PerfectSpecular() = default;
        
        // Calculate colors.
        virtual RGBColor f(const ShadeInfo &sinfo, const Vector3D &wo, const Vector3D &wi) const;

        virtual RGBColor sample_f(const ShadeInfo &sinfo, const Vector3D &wo, Vector3D &wi) const;

        virtual RGBColor sample_f(const ShadeInfo &sinfo, const Vector3D &wo, Vector3D &wi, float &pdf) const;

        virtual RGBColor rho(const ShadeInfo &sinfo, const Vector3D &wo) const;

        // Set data members.
        void set_kr(const float k);
        void set_cr(const RGBColor &c);
        void set_cr(const float r, const float g, const float b);
        void set_cr(const float c);
};