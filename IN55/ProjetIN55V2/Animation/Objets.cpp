#include "Objets.h"

#define TRIANGLE 0
#define QUADRILAT 1
#define POLYGONE 2

using namespace std;

Objet::Objet(QVector3D position, QVector3D orientation, QString nomObjet, QString fichierMesh, QString fichierTexture, bool textureUV, int repeatx, int repeaty)
{
    _position = position;
    _orientation = orientation;


    _nomObjet = nomObjet;
    _fichierMesh = fichierMesh;
    _nombreDeFaces = 0;
    _nombreDeVectrices = 0;
    _nombreDeCoordTexture = 0;
    _nombreDeCoordNormales = 0;
    _contientNormalVect = false;
    _isTextureUVMap = textureUV; //sert a  preciser si la texture doit etre affichee comme une texture UV map ou non
    _repeatx = repeatx;
    _repeaty = repeaty;
    _fichierTexture = fichierTexture;
    _chargementMeshOk = false;
    _chargementTextureOk = false;

}




