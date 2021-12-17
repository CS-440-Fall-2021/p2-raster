#pragma once

#include "BRDF.hpp"

/*

   Courtesy Kevin Suffern.

*/

class Lambertian: public BRDF
{
    private:
        float kd;
        RGBColor cd;
    
    public:
        // Constructor.
        Lambertian();

        // Copy constructor.
        Lambertian(const Lambertian& l);
        
        // Virtual copy constructor.
        virtual Lambertian* clone() const;

        // Destructor.
        virtual ~Lambertian() = default;
        
        // Calculate colors.
        virtual RGBColor f(const ShadeInfo& sinfo, const Vector3D& wo, const Vector3D& wi) const;
        
        virtual RGBColor sample_f(const ShadeInfo& sinfo, const Vector3D& wo, Vector3D& wi) const;
        
        virtual RGBColor sample_f(const ShadeInfo& sinfo, const Vector3D& wo, Vector3D& wi, float& pdf) const;
        
        virtual RGBColor rho(const ShadeInfo& sinfo, const Vector3D& wo) const;

        // Set data members.
        void set_ka(const float ka);
        void set_kd(const float kd);
        void set_cd(const RGBColor& c);
        void set_cd(const float r, const float g, const float b);
        void set_cd(const float c);
};