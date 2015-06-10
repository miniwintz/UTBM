#include "OpenGLWidget.h"

using namespace std;

OpenGLWidget::OpenGLWidget ( QWidget *parent, CameraLibre *cameraLibre, QVector3D positionCamera, QVector3D targetCamera) : QGLWidget ( parent ) //le ": QGLWidget (parent) sert a appeler le constructeur de parent(obligatoire)
{
    resize(800,600);

    p_cameraLibre = cameraLibre;

    m_positionCamera = positionCamera;
    m_cibleCamera = targetCamera;

    basis = new Basis(10);

    setFormat ( QGLFormat ( QGL::DoubleBuffer | QGL::DepthBuffer ) );

    loadSkybox();
}

void OpenGLWidget::initializeGL()
{

    qglClearColor ( Qt::black );


    /////////////////////Eclairage/////////////////////////////////////
    float ambientColor[4] = {0.7f,0.7f,0.7f,1.0f};

    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

    float global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    glEnable(GL_DEPTH_TEST);	// Active le test de profondeur
    glEnable(GL_LIGHTING);          // Active l'éclairage
    glEnable(GL_LIGHT0);            // Active light0
        glLightfv(GL_LIGHT0,GL_AMBIENT,ambientColor);
        glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION ,0.1f);

    /*config reflection lumière sur les matériaux*/
  //  float qaGreen[] = {0.0,1.0,0.0,1.0};
    float qaWhite[] = {1.0,1.0,1.0,1.0};
    float qaGrey[] = {0.42,0.42,0.42,1.0};

   // glMaterialfv(GL_FRONT,GL_AMBIENT,qaWhite);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,qaGrey);
    glMaterialfv(GL_FRONT,GL_SPECULAR,qaWhite);
    glMaterialf(GL_FRONT,GL_SHININESS,60.0);
    /*fin config lum*/

    g_model.loadModel( "data/meshes/monster.md5mesh" );
    loadSkybox();
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


void OpenGLWidget::loadSkybox()
{
    cube_map_texture_ID[0]=loadTexture("sky/jajalien1_front",false);
    cube_map_texture_ID[3]=loadTexture("sky/jajalien1_back",false);
    cube_map_texture_ID[2]=loadTexture("sky/jajalien1_left",false);
    cube_map_texture_ID[1]=loadTexture("sky/jajalien1_right",false);
    cube_map_texture_ID[4]=loadTexture("sky/jajalien1_top",false);
  //  cube_map_texture_ID[5]=loadTexture("sky/down",false);

}

void OpenGLWidget::drawSkybox()
{
    // Réglage de l'orientation
    glPushMatrix();
int scaleValue = 500;
int transX = -200;


glBindTexture(GL_TEXTURE_2D,cube_map_texture_ID[2]); //FRONT
    glBegin(GL_QUADS);
        glTexCoord2d(0,0);glVertex3d(scaleValue+transX,0+transX,0);
        glTexCoord2d(0,1);glVertex3d(scaleValue+transX,0+transX,300);
        glTexCoord2d(1,1);glVertex3d(0+transX,0+transX,300);
        glTexCoord2d(1,0); glVertex3d(0+transX,0+transX,0);
    glEnd();



glBindTexture(GL_TEXTURE_2D,cube_map_texture_ID[0]); //LEFT
    glBegin(GL_QUADS);
        glTexCoord2d(0,0); glVertex3d(0+transX,0+transX,0);
        glTexCoord2d(0,1); glVertex3d(0+transX,0+transX,300);
        glTexCoord2d(1,1); glVertex3d(0+transX,scaleValue+transX,300);
        glTexCoord2d(1,0); glVertex3d(0+transX,scaleValue+transX,0);
    glEnd();



glBindTexture(GL_TEXTURE_2D,cube_map_texture_ID[3]); //RIGHT
    glBegin(GL_QUADS);
        glTexCoord2d(0,0); glVertex3d(scaleValue+transX,scaleValue+transX,0);
        glTexCoord2d(0,1);glVertex3d(scaleValue+transX,scaleValue+transX,300);
        glTexCoord2d(1,1);glVertex3d(scaleValue+transX,0+transX,300);
        glTexCoord2d(1,0);glVertex3d(scaleValue+transX,0+transX,0);
    glEnd();



glBindTexture(GL_TEXTURE_2D,cube_map_texture_ID[1]); //BACK
    glBegin(GL_QUADS);
        glTexCoord2d(0,0); glVertex3d(0+transX,scaleValue+transX,0);
        glTexCoord2d(0,1); glVertex3d(0+transX,scaleValue+transX,300);
        glTexCoord2d(1,1); glVertex3d(scaleValue+transX,scaleValue+transX,300);
        glTexCoord2d(1,0); glVertex3d(scaleValue+transX,scaleValue+transX,0);
    glEnd();


//glBindTexture(GL_TEXTURE_2D,cube_map_texture_ID[5]); // DOWN
//glBegin(GL_QUADS);

//    glTexCoord2d(1,0); glVertex3d(scaleValue+transX,0+transX,0);
//    glTexCoord2d(1,1); glVertex3d(scaleValue+transX,scaleValue+transX,0);
//    glTexCoord2d(0,1); glVertex3d(0+transX,scaleValue+transX,0);
//    glTexCoord2d(0,0);  glVertex3d(0+transX,0+transX,0);
//glEnd();

glBindTexture(GL_TEXTURE_2D,cube_map_texture_ID[4]); // UP
glBegin(GL_QUADS);

    glTexCoord2d(0,0);glVertex3d(0+transX,0+transX,300);
    glTexCoord2d(0,1);glVertex3d(scaleValue+transX,0+transX,300);
    glTexCoord2d(1,1);glVertex3d(scaleValue+transX,scaleValue+transX,300);
    glTexCoord2d(1,0);glVertex3d(0+transX,scaleValue+transX,300);
glEnd();


glPopMatrix();
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


    basis->drawShape();

    glEnable ( GL_TEXTURE_2D );
    drawSkybox();

    // Rendu du modele
    g_model.m_update(0.05);
    g_model.render();
}

