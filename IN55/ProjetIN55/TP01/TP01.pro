######################################################################
# Automatically generated by qmake (2.01a) Sun Mar 6 14:27:38 2011
######################################################################

CONFIG += console release
QT += core gui opengl
TARGET = TP01
TEMPLATE = app

DEPENDPATH += src
INCLUDEPATH = ../Common/ src "../glew-mingw\include"
LIBS += -L"../glew-mingw\lib" -lglew32

DESTDIR = release
OBJECTS_DIR = obj

# Input
HEADERS += \
    ../Common/GlFramework.h \
    ../Common/GlWindow.h \
    ../Common/LF_String.h \
    ../Common/Object3D.h \
    ../Common/Shapes/Basis.h \
    ../Common/Shapes/MeshBuilder.h \
    src/tiny_obj_loader.h

SOURCES += \
    ../Common/GlFramework.cpp \
    ../Common/GlWindow.cpp \
    ../Common/LF_String.cpp \
    ../Common/Object3D.cpp \
    ../Common/Shapes/Basis.cpp \
    src/TP01.cpp \
    src/main.cpp \
    ../Common/Shapes/MeshBuilder.cpp \
    src/tiny_obj_loader.cpp
