#ifndef CAMERALIBRE_H
#define CAMERALIBRE_H

#include <cmath>
#include <vector>
#include <iostream>

#include <QVector3D>


class CameraLibre
{
        public:
                CameraLibre(QVector3D position, QVector3D cibleCamera, QVector3D orientation, float vitessecameraLibre = 0, float sensivite = 0);

                //fonction la plus utilisée, elle est appelée a  chaque fois que l'on rafraichit l'image (pour deplacer la camera par exemple)
                void Animate();

                void mouvementCameraSouris (int new_x, int new_y);
                void deplacement (int numDirection, bool valeur);

                void setVitesse(float speed);
                float getVitesse();

                QVector3D getCibleCamera();
                QVector3D getPosition();

                void setPosition(QVector3D m_position);
                float sensivity;
                float theta;
                float phi;

        private:
                void conversionAnglesVersVecteurs();

                float m_vitesse;

                bool m_mouvementCamera[6];

                QVector3D m_position;
                QVector3D m_orientation;

                QVector3D m_cibleCamera; //contient les coordonnees du point que le cameraLibre regarde

                //contient les coord du vecteur de la direction que le cameraLibre regarde, le calcul entre _targetcameraLibre et m_forward sont effectuee par les fonctions conversionAnglesVersVecteurs() et conversionVecteursVersAngles()
                QVector3D m_forward;
                QVector3D m_up; //Vecteur vertical du monde, utilisé dans les calculs
                QVector3D m_left; //Vecteur qui montre la gauche (orthogonal au sens de deplacement et au vecteur m_up)
};


#endif // CAMERALIBRE_H
