#include "clmanager.h"
#include "particlesystemwindow.h"
#include "particlesystemwindow.h"
#include "utils.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    QSurfaceFormat format;
    format.setSamples(16);

    ParticleSysWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();
    
    // CLManager clManager;
    // clManager.computeMemory(particleManager);

    window.setAnimating(true);

    return app.exec();
}
