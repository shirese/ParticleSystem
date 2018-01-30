#ifndef PARTICLESYSTEMWINDOW_H
#define PARTICLESYSTEMWINDOW_H

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

        void initialize(ParticleManager &particleManager, CLManager &clManager) override;
        void render(ParticleManager &particleManager, CLManager &clManager) override;

    protected:
        float x = 0, y = 0;
        GLuint m_posAttr;
        GLuint m_colAttr;
        GLuint m_matrixUniform;
        void mouseMoveEvent(QMouseEvent *event);
        void keyPressEvent(QKeyEvent *event);

    private:
        int m_frame;
        bool m_update = false;
        bool m_followMouse = true;
        bool m_gravitySet = false;
        QOpenGLShaderProgram* m_program;
        QOpenGLBuffer m_colVBO, m_posVBO;
        QOpenGLVertexArrayObject m_vao;
        QVector3D m_gravityVec;
};

#endif // PARTICLESYSTEMWINDOW_H
