#include "../utilities/RGBColor.hpp"
#include "../utilities/Ray.hpp"


class World;

class Tracer
{
    protected:
    World *world_ptr;

    public:

    Tracer();

    Tracer(World* w_ptr);

    virtual ~Tracer() = default;

    virtual RGBColor trace_ray(const Ray &ray, const int depth) const = 0;
};