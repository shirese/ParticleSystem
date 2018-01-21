#ifndef PARTICLEMANAGER
#define PARTICLEMANAGER

#include <QtGui/QOpenGLFunctions>
#include <QVector3D>

class ParticleManager
{
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
        float *m_gravityCenter;
        GLuint m_vao, m_vbo;

};

#endif
