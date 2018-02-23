#include "particlesystemwindow.h"
#include "shader.h"
#include "utils.h"

ParticleManager::~ParticleManager()
{
    glDisableVertexAttribArray(0);
//    glDeleteBuffers(1, &m_posVBO);
//    glDeleteBuffers(1, &m_colVBO);
//    glDeleteVertexArrays(1, &m_vao);
}

void ParticleManager::renderParticles()
{
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    // glBindVertexArray(_vao);
    // glUseProgram(m_program);
    // glDrawArrays(GL_POINTS, 0, PARTICLES_COUNT);
    // glUseProgram(0);
    // glBindVertexArray(0);
}

void ParticleManager::generateBuffers(GLuint posAttr, GLuint colAttr)
{
    GLenum err;
     GLfloat vertices[] = {
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
    };
    GLfloat colors[] = {
        1.0f, 0.0f,  0.0f,
        0.0f, 1.0f,  0.0f,
        0.0f, 0.0f,  1.0f
    };
    // int sizeParticleBuffer = (GLuint)PARTICLES_COUNT * sizeof(Particle);
    int sizeParticleBuffer = 9 * sizeof(GLfloat);
    int sizeColorBuffer = 9 * sizeof(GLfloat);
    
    printf("Generate buffers.\n");

    // Create VAO
    m_vao.create();
    m_vao.bind();

    /* Gen and Lock pos VBO */
    // m_posVBO = 0;
    // glGenBuffers(1, &m_posVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, m_posVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeParticleBuffer, vertices, GL_STREAM_DRAW);
    m_posVBO.create();
    m_posVBO.setUsagePattern( QOpenGLBuffer::DynamicDraw );
    m_posVBO.allocate(sizeParticleBuffer);

    m_colVBO.create();
    m_colVBO.setUsagePattern( QOpenGLBuffer::DynamicDraw );
    m_colVBO.bind();
    m_colVBO.allocate(sizeColorBuffer);
    /* Gen and Lock col VBO */
    // m_colVBO = 0;
    // glGenBuffers(1, &m_colVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, m_colVBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeColorBuffer, colors, GL_STREAM_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, sizeParticleBuffer, nullptr, GL_STREAM_DRAW);
    // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeParticleBuffer, vertices);
    // glBufferSubData(GL_ARRAY_BUFFER, sizeParticleBuffer, sizeColorBuffer, colors);

    /* Gen and Lock VAO */
    // m_vao = 0;
    // glGenVertexArrays(1, &m_vao);
    // glBindVertexArray(m_vao);
    // Lock VBO
    // glBindBuffer(GL_ARRAY_BUFFER, m_posVBO);
    // Access vertices in memory
    // glVertexAttribPointer(posAttr, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    // glEnableVertexAttribArray(posAttr);
    // glVertexAttribPointer(colAttr, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeParticleBuffer));
    // glBindBuffer(GL_ARRAY_BUFFER, m_colVBO);
    // glVertexAttribPointer(colAttr, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    // glEnableVertexAttribArray(colAttr);


    // /* Gen and Lock col VBO */
    // glGenBuffers(1, &m_colVBO);
    // glBindBuffer(GL_ARRAY_BUFFER, m_colVBO);

    // // Load buffer data
    // glBufferData(GL_ARRAY_BUFFER, sizeColorBuffer, nullptr, GL_STREAM_DRAW);
    // // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeParticleBuffer, vertices);
    // // glBufferSubData(GL_ARRAY_BUFFER, sizeParticleBuffer, sizeColorBuffer, colors);

    // // Unlock VBO
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // /* Lock VAO */
    // glBindVertexArray(m_vao);

    // // Lock VBO
    // glBindBuffer(GL_ARRAY_BUFFER, m_colVBO);

    // // Access vertices in memory
    // glVertexAttribPointer(colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);
    // glEnableVertexAttribArray(colAttr);
    // // glEnableVertexAttribArray(colAttr);

    // // Unlock VBO
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // // Unlock VAO
    // glBindVertexArray(0);
}

float *ParticleManager::getGravityCenter(void)
{
    return m_gravityCenter;
}

void ParticleManager::setGravityCenter(QVector3D pos)
{
    m_gravityCenter[0] = pos.x();
    m_gravityCenter[1] = pos.y();
    m_gravityCenter[2] = pos.z();
}

void ParticleManager::setParticleColor(float x, float y)
{
    GLfloat color_factor = x * y / (1480 * 1020);
    // GLuint colorBuffer;
    // GLuint colorBlockIndex;
    // GLuint bindingPoint;
    // GLint blockSize;

    // float r = x / 1480.f;
    // float g = y / 1020.f;
    // float b = (r + g) / 2;

    // printf("Set color: %f %f %f\n", r, g, b);

    // colorBlockIndex = glGetUniformBlockIndex(getShaderProgram(), "colorBlock");
    // glUniformBlockBinding(getShaderProgram(), colorBlockIndex, 1);

    // glGetActiveUniformBlockiv(getShaderProgram(), colorBlockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

    // GLubyte *blockBuffer = (GLubyte *)malloc(blockSize);

    // const GLchar *names[] = {"color_factor"};
    // GLuint indice[1];
    // glGetUniformIndices(getShaderProgram(), 1, names, indice);

    // GLint offset[1];
    // glGetActiveUniformsiv(getShaderProgram(), 1, indice, GL_UNIFORM_OFFSET, offset);

    // memcpy(blockBuffer + offset[0], &color_factor, sizeof(GLfloat));

    // glGenBuffers(1, &colorBuffer);
    // glBindBuffer(GL_UNIFORM_BUFFER, colorBuffer);
    // glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer, GL_DYNAMIC_DRAW);
    // glBindBufferBase(GL_UNIFORM_BUFFER, colorBlockIndex, colorBuffer);
    // GLuint c_id = glGetUniformLocation(getShaderProgram(), "color_in");
    // glUniform4fv(c_id, 1, color);
}

//ParticleManager::~ParticleManager()
//{
//    glDisableVertexAttribArray(0);
//    glDeleteBuffers(1, &m_posVBO);
//    // glDeleteProgram(m_program);
//    glDeleteVertexArrays(1, &m_vao);
//    delete(m_gravityCenter);
//}
