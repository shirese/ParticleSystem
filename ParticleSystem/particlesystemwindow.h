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

#include <QtCore/qmath.h>

#ifndef BUFFER_OFFSET

    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))

#endif

class ParticleSysWindow : public OpenGLWindow
{
    public:
        ParticleSysWindow();

        void initialize(ParticleManager &particleManager) override;
        void render(ParticleManager &particleManager) override;

    protected:
        GLuint m_posAttr;
        GLuint m_colAttr;
        GLuint m_matrixUniform;

    private:
        int m_frame;
        QOpenGLShaderProgram* m_program;
        
};

#endif // PARTICLESYSTEMWINDOW_H
