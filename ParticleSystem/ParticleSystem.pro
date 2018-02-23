TEMPLATE = app
TARGET = name_of_the_app

QT = core gui
CONFIG(release, debug|release) {
    CONFIG += optimize_full
}
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES +=  main.cpp \
    openglwindow.cpp \
    clmanager.cpp \
    particlemanager.cpp \
    utils.cpp \
    shader.cpp \
    particle.cpp \
    particlesystemwindow.cpp

HEADERS += \
    openglwindow.h \
    cl.hpp \
    clmanager.h \
    particlemanager.h \
    particlesystemwindow.h \
    utils.h \
    shader.h \
    particle.h \

LIBS += -F/System/Library/Frameworks/OpenCL.framework/
LIBS += -framework Cocoa
LIBS += -framework IOKit
LIBS += -framework CoreVideo
LIBS += -framework OpenCL
LIBS += -framework OpenGL