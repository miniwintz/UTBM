#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "MD5Model.h"
#include "Shapes/Basis.h"

class OpenGLWidget : public QGLWidget
{
public:

    OpenGLWidget (QWidget *parent, CameraLibre *cameraLibre, QVector3D positionCamera, QVector3D targetCamera);

    void loadSkybox();
    void drawSkybox();
    void initializeGL(); //initialisation des paramtres opengl, du fog, des textures,...
    void resizeGL ( int width, int height ); //est appele quand on cree le widget
    void paintGL(); //appelle apres lors des m_updateGL (quand on veut rafraichir)
    void conversionVecteursVersAngles();

    GLuint loadTexture ( QString filename, bool useMipMap); //chargement des textures

    MD5Model g_model;

private:
    GLuint cube_map_texture_ID[6];

    QVector3D m_positionCamera;
    QVector3D m_cibleCamera;

    //variables temporaires de calcul, utilisé seulement pour calculer la cible visée par la camera (fonction conversionVecteursVersAngles()...)
    QVector3D m_positioncameraLibre;
    QVector3D m_targetcameraLibre;

    float m_theta;
    float m_phi;

    CameraLibre *p_cameraLibre;

    Basis *p_basis;
};


#endif // OPENGLWIDGET_H
