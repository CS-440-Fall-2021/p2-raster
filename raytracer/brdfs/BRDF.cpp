#include "BRDF.hpp"

Point3D BRDF::sample_hemisphere() const
{
    std::uniform_real_distribution<double> unif(-1.0, 1.0);
    std::random_device rd;

    double x = unif(rd);
    double y = unif(rd);

    float cos_phi = cos(2.0 * PI * x);
    float sin_phi = sin(2.0 * PI * x);
    
    float cos_theta = pow((1.0 - y), 1.0 / (exp + 1.0));
    float sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    
    float pu = sin_theta * cos_phi;
    float pv = sin_theta * sin_phi;
    float pw = cos_theta;

    return Point3D(pu, pv, pw);
}