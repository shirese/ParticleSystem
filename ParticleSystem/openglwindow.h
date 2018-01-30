#include "clmanager.h"
#include "particlemanager.h"

#include <QMainWindow>
#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>

#include <QMouseEvent>

class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;

class OpenGLWindow : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWindow(QWindow *parent = 0);
    ~OpenGLWindow();

    virtual void render(QPainter *painter);
    virtual void render(ParticleManager &particleManager, CLManager &clManager);

    virtual void initialize(ParticleManager &particleManager, CLManager &clManager);

    void setAnimating(bool animating);

    public slots:
        void renderLater();
        void renderNow();

    protected:
        bool event(QEvent *event) override;
        void exposeEvent(QExposeEvent *event) override;
        QOpenGLContext *m_context;

    private:
        bool m_animating;

        QOpenGLPaintDevice *m_device;
};
