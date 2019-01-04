#include "particle.h"
#include "particlemanager.h"
#include "utils.h"

ParticleManager::ParticleManager()
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Create VBO
    glGenBuffers(1, &m_posVBO);
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_posVBO);
    // Alloc VBO
    glBufferData(GL_ARRAY_BUFFER, (GLuint)PARTICLES_COUNT * sizeof(Particle),
                nullptr, (GLuint)GL_STATIC_DRAW);
}

ParticleManager::~ParticleManager()
{
    glDeleteBuffers(1, &m_posVBO);
}

void ParticleManager::setAttributes(GLuint shaderProgram)
{
    m_posAttr = glGetAttribLocation(shaderProgram, "posAttr");
    m_colAttr = glGetAttribLocation(shaderProgram, "colAttr");
    m_matrixUniform = glGetUniformLocation(shaderProgram, "matrix");
    glEnableVertexAttribArray(m_posAttr);
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(0));
    glEnableVertexAttribArray(m_colAttr);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), BUFFER_OFFSET(sizeof(cl_float3)));
}
