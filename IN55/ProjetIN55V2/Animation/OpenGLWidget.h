#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "MD5Model.h"
#include "Shapes/Basis.h"

class OpenGLWidget : public QGLWidget
{
    public:
            OpenGLWidget (QWidget *parent, CameraLibre *cameraLibre, QVector3D positionCamera, QVector3D targetCamera);
            void initializeGL(); //initialisation des paramtres opengl, du fog, des textures,...
            void resizeGL ( int width, int height ); //est appele quand on cree le widget
            void paintGL(); //appelle apres lors des m_updateGL (quand on veut rafraichir)
            GLuint loadTexture ( QString filename, bool useMipMap); //chargement des textures


       void loadSkybox();
       void drawSkybox();

       GLuint cube_map_texture_ID[6];

            void conversionVecteursVersAngles();

            QVector3D m_positionCamera;
            QVector3D m_cibleCamera;
            float theta;
            float phi;

            CameraLibre *p_cameraLibre;
            QVector3D m_positioncameraLibre; //variables temporaires de calcul, utilisÃ© seulement pour calculer la cible visÃ© par la camera (fonction conversionVecteursVersAngles()...)
            QVector3D targetcameraLibre;

            MD5Model g_model;
            Basis *basis;
};


#endif // OPENGLWIDGET_H
