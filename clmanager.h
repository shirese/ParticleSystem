/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clmanager.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:21:31 by chaueur           #+#    #+#             */
/*   Updated: 2018/05/01 11:31:13 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLMANAGER_H
#define CLMANAGER_H

#define CL_CGL_SHAREGROUP_KHR 0x200C

#include <OpenGL/CGLCurrent.h>
#include "cl.hpp"
#include "particle.h"
#include "particlemanager.h"
#include "utils.h"

#include <iostream>

// #pragma OPENCL EXTENSION CL_APPLE_gl_sharing : enable

////////////////////////////////////////////////////////////////////////////////

#define KERNEL_INIT						("/Users/chaueur/ParticleSystem/kernel/init.cl")
#define KERNEL_HEADER					("/Users/chaueur/ParticleSystem/kernel/header.cl")
#define KERNEL_UPDATE					("/Users/chaueur/ParticleSystem/kernel/update.cl")
#define KERNEL_INIT_METHOD_NAME			("initialize")
#define KERNEL_UPDATE_METHOD_NAME		("update_position")

////////////////////////////////////////////////////////////////////////////////

class CLManager
{
    friend class Window;
    
    public:
        CLManager() {};
        virtual ~CLManager();
        void initCL();
        void computeMemory(GLuint posVBO);
        void runUpdateKernel(float *gravityPoint);
        void runInitKernel();
        void setShape (short s) { shape = s; };
        short shape;
        
    private:
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
