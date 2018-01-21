#include "particlesystemwindow.h"

ParticleSysWindow::ParticleSysWindow()
    :   m_frame(0)
{
}

void ParticleSysWindow::initialize(ParticleManager &particleManager)
{
    std::string vertexShaderSource, fragmentShaderSource;

    vertexShaderSource = fileToString(VERTEX_SHADER_SRC);
    if (vertexShaderSource.empty())
        exit(-1);
    fragmentShaderSource = fileToString(FRAGMENT_SHADER_SRC);
    if (fragmentShaderSource.empty())
        exit(-1);
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource.c_str());
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource.c_str());
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");
    particleManager.generateBuffers(m_posAttr, m_colAttr);
}

void ParticleSysWindow::render(ParticleManager &particleManager)
{
    GLuint err;
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
    m_program->setUniformValue(m_matrixUniform, matrix);

    glBindVertexArray(particleManager.m_vbo);
    glDrawArrays(GL_POINT, 0, PARTICLES_COUNT);
    glBindVertexArray(0);

    err = glGetError();
    if (err != GL_NO_ERROR)
        printf("Error: OpenGL Get Error: %d\n", err);
    m_program->release();

    ++m_frame;
}
