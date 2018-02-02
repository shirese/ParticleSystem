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

    int sizeParticleBuffer = (GLuint)PARTICLES_COUNT * sizeof(Particle);
    
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
    // m_program->setAttributeBuffer( m_posAttr, GL_FLOAT, 0, 3, sizeof(Particle) );
    m_program->enableAttributeArray( m_colAttr );
    m_program->setAttributeBuffer( m_posAttr, GL_FLOAT, 0, 3, sizeof(Particle) );
    m_program->setAttributeBuffer( m_colAttr, GL_FLOAT, 1 * sizeof(cl_float3), 3, sizeof(Particle) );
    
    /////////////////////////// COLOR BUFFER ///////////////////////////////////
    // m_program->setAttributeBuffer( m_colAttr, GL_FLOAT, 0, 3 );

    m_matrixUniform = m_program->uniformLocation("matrix");
    clManager.computeMemory(m_posVBO);
    clManager.setShape(m_initShape);
    clManager.runInitKernel();
    // particleManager.generateBuffers(m_posAttr, m_colAttr);
    m_program->release();
}

void ParticleSysWindow::render(ParticleManager &particleManager, CLManager &clManager)
{
    GLuint err;
    const qreal retinaScale = devicePixelRatio();

    // float grav[3] = { x, y, -2 };
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    // printf("{ %f %f %f }\n", gravityVec[0], gravityVec[1], gravityVec[2]);
    QMatrix4x4 model;
    model.setToIdentity();
    QMatrix4x4 projection;
    projection.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
    projection.translate(0, 0, -2);
    if (m_rotate)
        projection.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
    if (m_shapeUpdated)
    {
        clManager.setShape(m_initShape);
        clManager.runInitKernel();
        m_shapeUpdated = !m_shapeUpdated;
    }
    else if (m_update)
    {
        if (m_followMouse)
        {
            m_gravityVec.setX(2.0 * x / width() * retinaScale - 1.0);
            m_gravityVec.setY(1.0 - (2.0 * y) / height() * retinaScale);
            m_gravityVec.setZ(0);
        }
        m_gravityVec.project(model, projection, QRect(0, 0, width() * retinaScale, height() * retinaScale));
        float *grav = hit_plane(m_gravityVec, 2);
        printf("[0] %f %f %f\n", grav[0], grav[1], grav[2]);
        clManager.runUpdateKernel(grav);
    }
    m_program->setUniformValue(m_matrixUniform, projection);

    m_vao.bind();
    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_POINTS, 0, PARTICLES_COUNT);
    m_vao.release();
    // glBindVertexArray(particleManager.m_vao);
    // glBindVertexArray(0);

    m_program->release();

    // err = glGetError();
    // if (err != GL_NO_ERROR)
    //     printf("Error: OpenGL Get Error: %d\n", err);

    ++m_frame;
}

void ParticleSysWindow::mouseMoveEvent(QMouseEvent *event)
{
    x = event->x();
    y = event->y();
}

void ParticleSysWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Space:
            m_update = !m_update;
            break ;
        case Qt::Key_C:
            m_initShape = 1;
            m_shapeUpdated = !m_shapeUpdated;
            break ;
        case Qt::Key_V:
            m_initShape = 2;
            m_shapeUpdated = !m_shapeUpdated;
            break ;
        case Qt::Key_F:
            m_followMouse = !m_followMouse;
            break ;
        case Qt::Key_R:
            m_rotate = !m_rotate;
            break ;
        default:
            ;
    }
}
