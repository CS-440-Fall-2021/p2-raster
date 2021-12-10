#include "Tracer.hpp"

Tracer::Tracer()
{
    world_ptr = nullptr;
}

Tracer::Tracer(World *w_ptr)
{
    world_ptr = w_ptr;
}