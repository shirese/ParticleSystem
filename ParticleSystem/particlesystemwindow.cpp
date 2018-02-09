#include "particlesystemwindow.h"

ParticleSysWindow::ParticleSysWindow(QWidget *parent) : QOpenGLWidget(parent)
{
    QSurfaceFormat format;

    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSwapInterval(0);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    QSurfaceFormat::setDefaultFormat(format);
    setFormat(format);
    setMouseTracking(true);
    m_fpsLabel = new QLabel(this);
    m_fpsLabel->setFrameStyle(QFrame::NoFrame | QFrame::Plain);
    m_fpsLabel->setText("00");
    m_fpsLabel->setStyleSheet("QLabel { color : green; }");
    m_fpsLabel->setIndent(width() - 20);
    
    // QTimer* fpsTimer = new QTimer();

    // QObject::connect(fpsTimer, SIGNAL(timeout()), this, SLOT(showFps()));

    // fpsTimer->start(1000);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(0);
}

ParticleSysWindow::~ParticleSysWindow()
{
    m_posVBO.destroy();
    m_colVBO.destroy();
    m_program->release();
}

void ParticleSysWindow::showFPS()
{
    m_fpsLabel->setText(QString::number(m_fps));
    m_fps = 0;
}

void ParticleSysWindow::initializeGL()
{
    std::string vertexShaderSource, fragmentShaderSource;
    CLManager &clManager = CLManager::getInstance();

    initializeOpenGLFunctions();
    clManager.initCL(context());
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
}

void ParticleSysWindow::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    const qreal retinaScale = devicePixelRatio();    
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    m_projection.perspective(60.0f, w / float(h), 0.01f, 1000.0f);
    m_projection.translate(0, 0, -2);
}

void ParticleSysWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLuint err;
    CLManager &clManager = CLManager::getInstance();

    // m_program->bind();

    // printf("{ %f %f %f }\n", gravityVec[0], gravityVec[1], gravityVec[2]);
    if (m_rotate)
        m_projection.rotate(100.0f * m_frame / 60.0, 0, 1, 0);
        // m_projection.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);
    if (m_shapeUpdated)
    {
        clManager.setShape(m_initShape);
        clManager.runInitKernel();
        m_shapeUpdated = false;
        m_shapeUpdating = true;
    }
    else if (clManager.shape == 0)
    {
        m_shapeUpdated = false;
        m_shapeUpdating = false;
        m_initShape = 0;
        m_update = false;
        m_followMouse = false;
    }
    if (m_shapeUpdating)
        clManager.runInitKernel();
    else if (m_update)
    {
        if (m_followMouse)
        {
            m_gravityVec.setX(2.0 * x / width() - 1.0);
            m_gravityVec.setY(1.0 - (2.0 * y) / height());
            // m_gravityVec.setZ(0);
        }
        float *grav = hit_plane(m_gravityVec, 2);
        clManager.runUpdateKernel(grav);
    }
    m_program->setUniformValue(m_matrixUniform, m_projection);

    m_vao.bind();
    glDrawArrays(GL_POINTS, 0, PARTICLES_COUNT);
    m_vao.release();
    // glBindVertexArray(particleManager.m_vao);
    // glBindVertexArray(0);

    // m_program->release();

    // err = glGetError();
    // if (err != GL_NO_ERROR)
    //     printf("Error: OpenGL Get Error: %d\n", err);
    glEnd();
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
            m_shapeUpdating = false;
            break ;
        case Qt::Key_C:
            m_initShape = 1;
            m_shapeUpdated = true;
            m_update = true;
            break ;
        case Qt::Key_V:
            m_initShape = 2;
            m_shapeUpdated = true;
            m_update = true;
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
