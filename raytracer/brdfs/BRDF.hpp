#pragma once

#include "../utilities/Constants.hpp"
#include "../utilities/RGBColor.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Vector3D.hpp"

#include <math.h>
#include <random>

/*

   Courtesy Kevin Suffern.

*/

class BRDF
{
    protected:
        float exp;

    public:
        // Constructor.
        BRDF() = default;

        // Copy constructor and assignment operator.
        BRDF(const BRDF& camera) = default;
        BRDF& operator=(const BRDF& other) = default;

        // Virtual copy constructor.
        virtual BRDF* clone() const = 0;

        // Destructor.
        virtual ~BRDF() = default;

        // Calculate colors.
        virtual RGBColor f(const ShadeInfo& sinfo, const Vector3D& wo, const Vector3D& wi) const = 0;
        
        virtual RGBColor sample_f(const ShadeInfo& sinfo, const Vector3D& wo, Vector3D& wi) const = 0;
        
        virtual RGBColor sample_f(const ShadeInfo& sinfo, const Vector3D& wo, Vector3D& wi, float& pdf) const = 0;
        
        virtual RGBColor rho(const ShadeInfo& sinfo, const Vector3D& wo) const = 0;


        Point3D sample_hemisphere() const;
};