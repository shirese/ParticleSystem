#ifndef PARTICLEMANAGER
#define PARTICLEMANAGER

#include <QtGui/QOpenGLFunctions>
#include <QVector3D>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class ParticleManager
{
    friend class OpenGLWindow;
    friend class ParticleSysWindow;
    friend class CLManager;

    public:
        ParticleManager() {};
        virtual ~ParticleManager();
        float *getGravityCenter();
        void generateBuffers(GLuint posAttr, GLuint colAttr);
        void setGravityCenter(QVector3D pos);
        void setParticleColor(float x, float y);
        void renderParticles();

    protected:
        unsigned int m_nbParticles;
        float m_gravityCenter[3] = {0., 0., -1.};
        QOpenGLBuffer m_colVBO, m_posVBO;
        QOpenGLVertexArrayObject m_vao;
};

#endif
