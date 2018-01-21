#include "particlesystemwindow.h"
#include "shader.h"
#include "utils.h"

ParticleManager::~ParticleManager(){ }

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

    /* Create and lock VAO */
   glGenVertexArrays(1, &m_vao);
   glBindVertexArray(m_vao);

    /* Create and lock VBO which contains vertices and colors */
   glGenBuffers(1, &m_vbo);
   glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // Load buffer data
    glBufferData(GL_ARRAY_BUFFER, (GLuint)PARTICLES_COUNT * sizeof(Particle), nullptr, GL_STREAM_DRAW);

    // Access vertices in memory
    glVertexAttribPointer(posAttr, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glVertexAttribPointer(colAttr, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(posAttr);
    glEnableVertexAttribArray(colAttr);

    // Unblock VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Unblock VAO
    glBindVertexArray(0);

    err = glGetError();
	if (err != GL_NO_ERROR)
		printf("Error: OpenGL Get Error: %d\n", err);
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
//    glDeleteBuffers(1, &m_vbo);
//    // glDeleteProgram(m_program);
//    glDeleteVertexArrays(1, &m_vao);
//    delete(m_gravityCenter);
//}
