#include "clmanager.h"
#include "particlesystemwindow.h"
#include "utils.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    ParticleSysWindow window;
    window.resize(1280, 1050);
    window.show();
    
    return app.exec();
}
