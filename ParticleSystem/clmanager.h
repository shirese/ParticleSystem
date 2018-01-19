#ifndef CLMANAGER_H
#define CLMANAGER_H

#include "cl.hpp"
#include "particlesystemwindow.h"

#include <iostream>

////////////////////////////////////////////////////////////////////////////////

#define KERNEL_MAIN						("/Users/chaueur/ParticleSystem/ParticleSystem/kernel/main.cl")
#define KERNEL_HEADER					("/Users/chaueur/ParticleSystem/ParticleSystem/kernel/header.cl")
#define KERNEL_UPDATE					("/Users/chaueur/ParticleSystem/ParticleSystem/kernel/update.cl")
#define KERNEL_INIT_METHOD_NAME			("initialize_sphere")
#define KERNEL_UPDATE_METHOD_NAME		("update_position")

////////////////////////////////////////////////////////////////////////////////

class CLManager
{
    public:
        CLManager();
        void computeMemory(ParticleManager &particleManager);

    private:
        cl::Context     m_context;
        cl::Kernel      m_initKernel;
        cl::Kernel      m_updateKernel;
        cl::Buffer      m_bufferGravity;
        cl::BufferGL    m_bufferVBO;
};

#endif // CLMANAGER_H
