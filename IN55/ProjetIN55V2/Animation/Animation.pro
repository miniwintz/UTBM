#-------------------------------------------------
#
# Project created by QtCreator 2014-03-26T17:14:40
#
#-------------------------------------------------

DEPENDPATH += src
INCLUDEPATH = ../Common/ src

TARGET = Animation
TEMPLATE = app

QT       += core gui
QT       += opengl
QT       += widgets multimedia

SOURCES += ../Common/Shapes/Basis.cpp \
    main.cpp\
    MainWindow.cpp \
    OpenGLWidget.cpp \
    CameraLibre.cpp \
    MD5Model.cpp \
    MD5Animation.cpp


HEADERS  += ../Common/Shapes/Basis.h \
    MainWindow.h \
    OpenGLWidget.h \
    CameraLibre.h \
    MD5Model.h \
    MD5Animation.h


