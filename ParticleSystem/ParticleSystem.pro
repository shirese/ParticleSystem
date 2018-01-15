TEMPLATE = app
TARGET = name_of_the_app

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES +=  main.cpp \
    openglwindow.cpp \
    clmanager.cpp

HEADERS += \
    openglwindow.h \
    cl.hpp \
    clmanager.h

LIBS += -F/System/Library/Frameworks/OpenCL.framework/
LIBS += -framework OpenCL
