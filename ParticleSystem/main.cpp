#include "clmanager.h"
#include "particlesystemwindow.h"
#include "utils.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    QSurfaceFormat format;
    format.setSamples(16);
    format.setVersion( 4, 1 );
    format.setProfile(QSurfaceFormat::CoreProfile);

    ParticleSysWindow window;
    window.setFormat(format);
    window.resize(1280, 1050);
    window.show();
    
    // CLManager clManager;
    // clManager.computeMemory(particleManager);

    window.setAnimating(true);

    return app.exec();
}
