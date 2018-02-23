/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particlemanager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaueur <chaueur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:22:45 by chaueur           #+#    #+#             */
/*   Updated: 2018/02/22 18:56:19 by chaueur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTICLEMANAGER

# define PARTICLEMANAGER

# include <OpenGL/gl3.h>

# include <glm/vec3.hpp> // glm::vec3

class ParticleManager
{
    public:
        ParticleManager();
        virtual ~ParticleManager();
        void setAttributes(GLuint shaderProgram);
        GLuint getPosVBO(){ return (m_posVBO); };
        GLuint getVAO(){ return (m_vao); };
        GLuint getMatrixUniform(){ return (m_matrixUniform); };
        glm::vec3 gravityVec;

    private:
        GLuint m_posVBO, m_vao;
        GLint m_posAttr, m_colAttr, m_matrixUniform;
        // GLM PROJ + GRAV VEC3 HERE
};

#endif
