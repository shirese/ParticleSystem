#ifndef PARTICLE_H
#define PARTICLE_H

#include "cl.hpp"

class Particle
{
    public:
        Particle();
        cl_float3 position;
        cl_float3 velocity;
};

#endif // PARTICLE_H
