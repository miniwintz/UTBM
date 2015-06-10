﻿//*****************************************************************************
//
// Class: Basis
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//         (Associate Professor at the
//          "Université de Technologie de Belfort-Montbéliard", France)
// Version: 1.0
// Last update: 2014-04-02
//
//*****************************************************************************


#include "Shapes/Basis.h"


GLfloat g_TabColors[] =
{
    1.0f, 0.0f, 0.0f,
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f
};


Basis::Basis( GLfloat length )
{
    for( GLuint i = 0; i < 6*3; ++i )
    {
        m_TabVertices[i] = 0.0f;
    }

    m_TabVertices[3] = length;
    m_TabVertices[10] = length;
    m_TabVertices[17] = length;
}

Basis::~Basis()
{

}


void
Basis::drawShape()
{
  // X : rouge
  // Y : vert
  // Z : bleu

    glEnableClientState( GL_VERTEX_ARRAY );
     glEnableClientState( GL_COLOR_ARRAY );
     glColorPointer(3, GL_FLOAT,0,g_TabColors);
      glVertexPointer( 3, GL_FLOAT, 0, m_TabVertices );
      glDrawArrays( GL_LINES, 0, 6 );

glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );



}