#include "OpenGLWidget.h"

using namespace std;

OpenGLWidget::OpenGLWidget ( QWidget *parent, CameraLibre *cameraLibre, QVector3D positionCamera, QVector3D targetCamera) : QGLWidget ( parent ) //le ": QGLWidget (parent) sert a appeler le constructeur de parent(obligatoire)
{
    resize(800,600);

    p_cameraLibre = cameraLibre;

    m_positionCamera = positionCamera;
    m_cibleCamera = targetCamera;

    setFormat ( QGLFormat ( QGL::DoubleBuffer | QGL::DepthBuffer ) );
}

void OpenGLWidget::initializeGL()
{
    g_model.loadModel( "Meshs/boarman/boarman.md5mesh" );
}

GLuint OpenGLWidget::loadTexture ( QString filename, bool useMipMap)
{
        QImage baseTexture, interTexture;
        GLuint finalTexture;

        if (!baseTexture.load ( filename, "PNG" ))
            qDebug() << "----->ERREUR 02 ; Chargement texture = FAILED";

        interTexture = QGLWidget::convertToGLFormat ( baseTexture ); //transformation et renversement de l'image
        glGenTextures ( 1, &finalTexture ); //generation de la texture openGL, Ã  ce niveau ont pourrait renvoyer finalTexture

        glBindTexture ( GL_TEXTURE_2D, finalTexture );


        if ( useMipMap )
        {
                gluBuild2DMipmaps ( GL_TEXTURE_2D, 3, interTexture.width(), interTexture.height(), GL_RGBA, GL_UNSIGNED_BYTE,
                                    interTexture.bits() );//creation des 3 mipmaps (adapte a  chaque distance)

                glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR ); //ajout du filtre trilineaire pour le "tres beau rendu"
                glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); //filtre lineaire pour longue distance
        }
        else
        {
                glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); //ajout seulement d'un filtre lineaire
                glTexImage2D ( GL_TEXTURE_2D, 0, 3, interTexture.width(), interTexture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, interTexture.bits() );
        }

        return finalTexture; //on renvoie la texture

}


/*REPERE*/
void OpenGLWidget::dessinerRepere()
{

}

void OpenGLWidget::conversionVecteursVersAngles() //transforme les coordonnÃ©es X,Y,Z en phi et theta
{
        //Calcul des angles à  partir des coordonnees X,Y,Z :
        //Une coordonnee spherique est de forme (r, phi, theta)
        //Pour les coordonnees spherique (r,theta,phi) on a phi langle à partir de laxe vertical z
        //et theta langle à partir de laxe x
        //r = racine( x² + y² + z² )
        //phi = arcos ( Z / r)
        //theta = arcos ( X / racine(X²+Y²) )
        //-La librairie <cmath> utilise les radians! C'est pour cela qu'il faut convertir à chaque fois les degrÃ©s...

        QVector3D m_forward(targetcameraLibre.x() - (m_positioncameraLibre.x()+1),targetcameraLibre.y() - (m_positioncameraLibre.y()+1),targetcameraLibre.z() - (m_positioncameraLibre.z()+6));

        float r = sqrt(pow(m_forward.x(),2) + pow(m_forward.y(),2) + pow(m_forward.z(),2));
        phi = ( acos(m_forward.z()/r)  *180/M_PI);

        float r_temp = sqrt(pow(m_forward.x(),2) + pow(m_forward.y(),2));

        if (m_forward.y() >= 0)
        {
                theta = ( (acos(m_forward.x()/r_temp)) * 180/M_PI);
        }
        else
        {
                theta = - (  (acos(m_forward.x()/r_temp)) * 180/M_PI);
        }
}


void OpenGLWidget::resizeGL ( int width, int height )
{
    glViewport ( 0, 0, width, height );
    glMatrixMode ( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective ( 70, ( float ) 640/480,1,1000 );
}

void OpenGLWidget::paintGL()
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    ////////////////////////////////////
    /////Placement de la camera//////
    ////////////////////////////////////
    m_positioncameraLibre = (*p_cameraLibre).getPosition();
    targetcameraLibre = (*p_cameraLibre).getCibleCamera();

    m_positionCamera.setX(m_positioncameraLibre.x()+1);
    m_positionCamera.setY(m_positioncameraLibre.y()+1);
    m_positionCamera.setZ(m_positioncameraLibre.z()+6);

    m_cibleCamera = targetcameraLibre;
    gluLookAt(m_positionCamera.x(),m_positionCamera.y(),m_positionCamera.z(),m_cibleCamera.x(),m_cibleCamera.y(),m_cibleCamera.z(),0,0,1);

    // Rendu du modele
    g_model.m_update(0.05);
    g_model.render();
}

