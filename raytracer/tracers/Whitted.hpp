#include "Tracer.hpp"

class Whitted: public Tracer
{
    public:
    Whitted();

    Whitted(World *w_ptr);

    virtual ~Whitted() = default;

    RGBColor trace_ray(const Ray &ray, const int depth) const;
};