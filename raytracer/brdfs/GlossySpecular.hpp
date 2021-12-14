#pragma once

#include "BRDF.hpp"

/*

   Courtesy Kevin Suffern.

*/

class GlossySpecular: public BRDF
{
    private:
        float ks;
        RGBColor cs;

    public:
        // Constructor.
        GlossySpecular();
        
        // Copy constructor.
        GlossySpecular(const GlossySpecular& gs);

        // Virtual copy constructor
        virtual GlossySpecular* clone() const;

        // Destructor
        virtual ~GlossySpecular() = default;

        // Calculate colors.
        virtual RGBColor f(const ShadeInfo& sinfo, const Vector3D& wo, const Vector3D& wi) const;

        virtual RGBColor sample_f(const ShadeInfo& sinfo, const Vector3D& wo, Vector3D& wi) const;

        virtual RGBColor sample_f(const ShadeInfo& sinfo, const Vector3D& wo, Vector3D& wi, float& pdf) const;

        virtual RGBColor rho(const ShadeInfo& sinfo, const Vector3D& wo) const;

        // Set data members.
        void set_ks(const float ks);
        void set_exp(const float exp);
        void set_cs(const RGBColor& c);
        void set_cs(const float r, const float g, const float b);
        void set_cs(const float c);
};