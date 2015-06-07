#ifndef Basis_h
#define Basis_h


#include <QtOpenGL/QGLWidget>
#include <GL/gl.h>
#include <GL/glu.h>

class Basis
    //: public Object3D
{
    public:
        Basis( GLfloat length );
        virtual ~Basis();


        void drawShape();


    protected:
        GLfloat m_TabVertices[6*3];
};


#endif
