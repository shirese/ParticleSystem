#ifndef PARTICLE_H
#define PARTICLE_H

#define PARTICLES_COUNT 3072000

#include "cl.hpp"

class Particle
{
    public:
        Particle();
        cl_float3 position;
        cl_float3 color;
};

#endif // PARTICLE_H
