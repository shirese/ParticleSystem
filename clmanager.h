#ifndef CLMANAGER_H
#define CLMANAGER_H

#define CL_CGL_SHAREGROUP_KHR 0x200C

#include <OpenGL/CGLCurrent.h>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include "cl.hpp"
#include "particle.h"

#include <iostream>

#pragma OPENCL EXTENSION CL_APPLE_gl_sharing : enable

////////////////////////////////////////////////////////////////////////////////

#define KERNEL_MAIN						("/Users/chaueur/ParticleSystem/ParticleSystem/kernel/main.cl")
#define KERNEL_HEADER					("/Users/chaueur/ParticleSystem/ParticleSystem/kernel/header.cl")
#define KERNEL_UPDATE					("/Users/chaueur/ParticleSystem/ParticleSystem/kernel/update.cl")
#define KERNEL_INIT_METHOD_NAME			("initialize")
#define KERNEL_UPDATE_METHOD_NAME		("update_position")

////////////////////////////////////////////////////////////////////////////////

class CLManager
{
    public:
        static CLManager& getInstance()
        {
            static CLManager instance;

            return instance;
        };
        void initCL(QOpenGLContext *glContext);
        void computeMemory(QOpenGLBuffer &posVBO);
        void runUpdateKernel(float *gravityPoint);
        void runInitKernel();
        void setShape (short s) { shape = s; };
        short shape = 0;
        
    private:
        CLManager(){};
        CLManager(CLManager const &);
        void operator=(CLManager const &);
        cl::CommandQueue        m_cmdQueue;
        cl::Context             m_context;
        cl::Kernel              m_initKernel;
        cl::Kernel              m_updateKernel;
        cl::Buffer              m_bufferShape;
        cl::Buffer              m_bufferGravity;
        cl::BufferGL            m_bufferVBO;
        std::vector<cl::Memory> m_vbos;
        size_t                  m_maxWorkGroupSize;
};

#endif // CLMANAGER_H
