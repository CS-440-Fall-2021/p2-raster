#include "Tracer.hpp"

class Basic: public Tracer
{
    public:
    Basic();

    Basic(World *w_ptr);

    virtual ~Basic() = default;

    RGBColor trace_ray(const Ray &ray, const int depth) const;
};