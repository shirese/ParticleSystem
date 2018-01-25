#include "particlesystemwindow.h"

ParticleSysWindow::ParticleSysWindow()
    :   m_frame(0)
{
}

void ParticleSysWindow::initialize(ParticleManager &particleManager, CLManager &clManager)
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
    m_program->bind();

    GLfloat vertices[] = {
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
    };
    GLfloat colors[] = {
        1.0f, 0.0f,  0.0f,
        0.0f, 1.0f,  0.0f,
        0.0f, 0.0f,  1.0f,
    };
    // int sizeParticleBuffer = (GLuint)PARTICLES_COUNT * sizeof(Particle);
    // int sizeParticleBuffer = 9 * sizeof(GLfloat);
    int sizeParticleBuffer = 3 * sizeof(Particle);
    // int sizeParticleBuffer = 3 * sizeof(Particle);
    int sizeColorBuffer = 9 * sizeof(GLfloat);
    
    printf("Generate buffers.\n");

    // Create VAO
    m_vao.create();
    m_vao.bind();

    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");

    m_posVBO.create();
    m_posVBO.bind();
    m_posVBO.setUsagePattern( QOpenGLBuffer::StreamDraw );
    m_posVBO.allocate(sizeParticleBuffer);
    // m_posVBO.allocate(vertices, sizeParticleBuffer);
    m_program->enableAttributeArray( m_posAttr );
    m_program->setAttributeBuffer( m_posAttr, GL_FLOAT, 0, 3, sizeof(Particle) );
    // m_program->setAttributeBuffer( m_posAttr, GL_FLOAT, 0, PARTICLES_COUNT, sizeof(Particle) );
    
    m_colVBO.create();
    m_colVBO.bind();
    m_colVBO.setUsagePattern( QOpenGLBuffer::StreamDraw );
    m_colVBO.allocate(colors, sizeColorBuffer);
    m_program->enableAttributeArray( m_colAttr );
    m_program->setAttributeBuffer( m_colAttr, GL_FLOAT, 0, 3 );
    // m_program->setAttributeBuffer( m_colAttr, GL_FLOAT, 0, 3 );

    m_matrixUniform = m_program->uniformLocation("matrix");
    clManager.computeMemory(m_posVBO);
    clManager.runInitKernel();    
    // particleManager.generateBuffers(m_posAttr, m_colAttr);
    m_program->release();
}

void ParticleSysWindow::render(ParticleManager &particleManager, CLManager &clManager)
{
    GLuint err;
    const qreal retinaScale = devicePixelRatio();

    // clManager.runUpdateKernel(particleManager.m_gravityCenter);   
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -2);
    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
    m_program->setUniformValue(m_matrixUniform, matrix);

    m_vao.bind();
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    m_vao.release();
    // glBindVertexArray(particleManager.m_vao);
    // glBindVertexArray(0);

    m_program->release();

    // err = glGetError();
    // if (err != GL_NO_ERROR)
    //     printf("Error: OpenGL Get Error: %d\n", err);

    ++m_frame;
}
