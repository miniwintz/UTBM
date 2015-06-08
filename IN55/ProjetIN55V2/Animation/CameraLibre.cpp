#include "CameraLibre.h"

#define AVANCER 0
#define RECULER 1
#define GAUCHE 2
#define DROITE 3
#define MONTER 4
#define DESCENDRE 5


using namespace std;

CameraLibre::CameraLibre(QVector3D position, QVector3D cibleCamera, QVector3D orientation, float vitessecameraLibre, float sensitivite)

{
        m_cibleCamera = cibleCamera;
        m_position = position;
        m_orientation = orientation;

        m_mouvementCamera[AVANCER] = false;
        m_mouvementCamera[RECULER] = false;
        m_mouvementCamera[GAUCHE] = false;
        m_mouvementCamera[DROITE] = false;
        m_mouvementCamera[MONTER] = false;
        m_mouvementCamera[DESCENDRE] = false;

        m_vitesse = vitessecameraLibre; //pour la vitesse de deplacement
        sensivity = sensitivite;

        phi = 0;
        theta = 0;

        m_up = QVector3D(0,0,1);

}



void CameraLibre::Animate()
{
        if (m_mouvementCamera[AVANCER])
        {
            m_position += QVector3D(m_forward.x()* m_vitesse,m_forward.y() * m_vitesse,0);
        }
        if (m_mouvementCamera[RECULER])
        {
            m_position -= QVector3D(m_forward.x() * m_vitesse,m_forward.y() * m_vitesse,0);
        }
        if (m_mouvementCamera[GAUCHE])
        {
             m_position += m_left * m_vitesse;
        }
        if (m_mouvementCamera[DROITE])
        {
             m_position -= m_left * m_vitesse;
        }
        if (m_mouvementCamera[DESCENDRE])
        {
             m_position -= QVector3D(0,0,1);
        }
        if (m_mouvementCamera[MONTER])
        {
            m_position += QVector3D(0,0,1);
        }


        //comme on a bouge, on recalcule la cible fixee par la camera
        // en ajustant pour car la camera n'est pas exactement a la m_position du jour
        // mais decalé de (1,1,6)
        m_cibleCamera = QVector3D(m_forward.x() + (m_position.x() +1),m_forward.y() + (m_position.y() +1),m_forward.z() + (m_position.z() +6));

        //recalcule le vecteur perdendiculaire au vecteur up et target pour se deplacer vers la gauche ou la droite
        m_left = QVector3D::crossProduct(m_up,m_forward);
        m_left.normalize();
}

//tranforme les coordonnees phi et theta en vecteur qui donne la direction de la camera
void CameraLibre::conversionAnglesVersVecteurs()
{
        float r_temp = sin(phi*M_PI/180);
        m_forward = QVector3D(r_temp*cos(theta*M_PI/180),r_temp*sin(theta*M_PI/180),cos(phi*M_PI/180));
}

void CameraLibre::mouvementCameraSouris (int newX, int newY)
{
        theta += newX * sensivity; //on modifie les coordonnees polaire quand on bouge la souris
        phi -= newY * sensivity; //on met un moins car quand on regarde vers le bas phi augmente

        if (phi < 10) //On limite les valeurs de phi
        {
          phi = 10;
        }
        else if (phi > 170)
        {
          phi = 170;
        }


        if (theta > 180) //Evite d'avoir un angle de rotation lateral (theta donc) qui atteint 270°
        {
          theta = -180;
        }
        else if (theta < -180)
        {
          theta = 180;
        }

        m_orientation.setZ(theta);
        conversionAnglesVersVecteurs(); //et on convertit notre variation d'angle de vue en un vecteur (interpretable par la camera)
}


void CameraLibre::deplacement (int numDirection, bool valeur)
{
        if (numDirection <= 5)
        {
            m_mouvementCamera[numDirection] = valeur;
        }
        else
        {
            cout << "Erreur 03 ; m_mouvementCamera du personnage non-autorisé" << endl;
        }
}

void CameraLibre::setVitesse (float vitesse)
{
    m_vitesse = vitesse;
}

float CameraLibre::getVitesse()
{
    return m_vitesse;
}

QVector3D CameraLibre::getCibleCamera()
{
    return m_cibleCamera;
}

QVector3D CameraLibre::getPosition()
{
    return m_position;
}

void CameraLibre::setPosition(QVector3D m_position)
{
    m_position = m_position;
}

