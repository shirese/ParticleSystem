#ifndef PARTICLESYSTEMWINDOW_H
#define PARTICLESYSTEMWINDOW_H

#define PARTICLES_COUNT 1024000

#include "openglwindow.h"
#include "particle.h"
#include "shader.h"
#include "utils.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QScreen>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>
#include <QVector3D>

#include <QtCore/qmath.h>

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

class ParticleManager;
class ParticleSysWindow : public OpenGLWindow
{
    friend ParticleManager;

    public:
        ParticleSysWindow();
        void initialize();
        void render();

    protected:
        static GLuint m_posAttr;
        static GLuint m_colAttr;
        GLuint m_matrixUniform;

    private:
        int m_frame;
        QOpenGLShaderProgram* m_program;
        
};

class ParticleManager
{
    friend ParticleSysWindow;

    public:
        static ParticleManager& getInstance()
        {
            static ParticleManager instance;
            return instance;
        }
        float *getGravityCenter();
        GLuint getMatUniform();
        GLuint getVAO();
        GLuint getVBO();
        void generateBuffers();
        void setGravityCenter(QVector3D pos);
        void setParticleColor(float x, float y);
        void renderParticles();

    protected:
        unsigned int m_nbParticles;
        float *m_gravityCenter;
        GLuint m_vao, m_vbo;

    private:
        ParticleManager() {};
        ParticleManager(ParticleManager const&);
        void operator=(ParticleManager const&);

};

#endif // PARTICLESYSTEMWINDOW_H
