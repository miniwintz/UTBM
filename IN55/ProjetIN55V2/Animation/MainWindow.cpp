#include "MainWindow.h"
#include <QThread>

#define AVANCER 0
#define RECULER 1
#define GAUCHE 2
#define DROITE 3
#define SAUT 4
#define ACCROUPI 5

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QApplication::setOverrideCursor( QCursor( Qt::BlankCursor ));

    this->setWindowTitle("Projet IN55 - Animation");


    resize(800,600);
    fullscreen = false;

    mouseTracked = true;

    anti_repetition = false;

    QVector3D m_positionObjet;

    QVector3D m_orientationObjet;

    QVector3D m_cibleCamera;
    float m_vitessecameraLibre = 0.25;
    float sensivity = 0.1;

    QVector3D m_positionCamera;


    m_positionObjet.setX(29);
    m_positionObjet.setY(16);
    m_positionObjet.setZ(0);

    m_orientationObjet.setX(0);
    m_orientationObjet.setY(0);
    m_orientationObjet.setZ(0);

    m_cibleCamera.setX(36);
    m_cibleCamera.setY(26);
    m_cibleCamera.setZ(4);


    //de meme on cree le cameraLibre (qui hérite de la classe Objet), donc juste quelques membres et attributs en plus (voir Personnage.cpp et Objets.cpp)
    cameraLibre = new CameraLibre(m_positionObjet, m_cibleCamera, m_orientationObjet,m_vitessecameraLibre, sensivity);

    m_positionCamera = cameraLibre->getPosition();
    m_positionCamera += QVector3D(0,0,5);//Pour mettre la camera à 5 au dessus du sol
    m_cibleCamera = cameraLibre->getCibleCamera();

    QDesktopWidget widget;
    mainScreenSize = widget.availableGeometry(widget.primaryScreen());

    cout << "+ Resolution de l'écran : " << mainScreenSize.width() << "x" << mainScreenSize.height() << endl;
    vuePrincipal = new OpenGLWidget (this, cameraLibre, m_positionCamera, m_cibleCamera);

    setCentralWidget(vuePrincipal);

    timerJeu = new QTimer(this);
    connect(timerJeu, SIGNAL(timeout()), this, SLOT(cycleTimerJeu()));

    timerFPS = new QTimer(this);

    cout <<  "+ Chargement fenetre principale : OK" << endl;
    lancerJeu();

    this->setMouseTracking(true);
    vuePrincipal->setMouseTracking(true);
}

MainWindow::~MainWindow()
{

}

void MainWindow::lancerJeu()
{
        timerJeu->start(20);
        timerFPS->start(1000);
}


void MainWindow::stopperJeu()
{
        timerJeu->stop();
        timerFPS->stop();
}

void MainWindow::cycleTimerJeu()
{
    numCycle++;
    cameraLibre->Animate();

    vuePrincipal->updateGL();
}

void MainWindow::mouseMoveEvent ( QMouseEvent *event )
{
    if (!anti_repetition)//on verifie que ce n'est pas la fonction qui se rappelle elle meme (avec setPos) et que la souris est sur le bon widget
    {
            int xrel = (width()/2 - event->x());
            int yrel = ( height()/2 - event->y());

        cameraLibre->mouvementCameraSouris ( xrel, yrel );
        QPoint pos(width()/2,height()/2);
        QCursor::setPos(mapToGlobal(pos));

        anti_repetition = true;
    }
    else
    {
        anti_repetition = false;
    }
}



void MainWindow::wheelEvent ( QWheelEvent *event )
{
    float m_vitessecameraLibre = cameraLibre->getVitesse();

    if ( event->delta() >= 0 )
    {
        m_vitessecameraLibre += 0.5;
        //if (m_vitessecameraLibre > 6)
        //    m_vitessecameraLibre = 6;

        cameraLibre->setVitesse(m_vitessecameraLibre);
    }
    else
    {
        m_vitessecameraLibre -= 0.1;
        if (m_vitessecameraLibre < 0)
            m_vitessecameraLibre = 0;
        cameraLibre->setVitesse(m_vitessecameraLibre);
    }
    qDebug() << "Speed =" << m_vitessecameraLibre;
}


void MainWindow::keyPressEvent ( QKeyEvent *event )
{
    QVector3D _posi(cameraLibre->getPosition());


    switch ( event->key() )
    {
        case Qt::Key_Escape:
            qApp->exit();
            break;
        case Qt::Key_P:
            if ( !enPause )
            {
                enPause = true;
                stopperJeu();
            }
            else
            {
                enPause = false;
                lancerJeu();
            }
            break;
        case Qt::Key_Z:
            cameraLibre->deplacement ( AVANCER, true );
            break;
        case Qt::Key_S:
            cameraLibre->deplacement ( RECULER, true );
            break;
        case Qt::Key_Q:
            cameraLibre->deplacement ( GAUCHE, true );
            break;
        case Qt::Key_D:
            cameraLibre->deplacement ( DROITE, true );
            break;
        case Qt::Key_Control:
            qDebug() << "A genou";
            cameraLibre->deplacement ( ACCROUPI, true );
            break;
        case Qt::Key_Space:
            //qDebug() << "Space";
            cameraLibre->deplacement ( SAUT, true );
            break;
        case Qt::Key_Shift:
            qDebug() << "Pos = " << _posi.x() << _posi.y() << _posi.z();
            break;
        case Qt::Key_F1:
            if(fullscreen)
            {
                setWindowState(Qt::WindowNoState);
                fullscreen=false;
                qDebug() << "+ Window mode";
            }
            else
            {
                setWindowState(Qt::WindowFullScreen);
                fullscreen=true;
                qDebug() << "+ Full screen";
            }
            break;
        case Qt::Key_F2:
                mouseTracked = !mouseTracked;
                this->setMouseTracking(mouseTracked);
                vuePrincipal->setMouseTracking(mouseTracked);
                if(!mouseTracked)
                    QApplication::setOverrideCursor( QCursor());
                else
                    QApplication::setOverrideCursor( QCursor( Qt::BlankCursor ));
            break;



        case Qt::Key_N:
        {
            if(!event->isAutoRepeat()){
                vuePrincipal->g_model.loadAnim("Meshs/boarman/doom.md5anim");
              //  vuePrincipal->g_model.setIsWalking(true);
                vuePrincipal->g_model.getAnimation().setContinuous(true);
            }
        }
        break;
    }
}

void MainWindow::keyReleaseEvent ( QKeyEvent * event )
{


    switch ( event->key() )
    {
        case Qt::Key_Z:
            cameraLibre->deplacement ( AVANCER, false );
            break;
        case Qt::Key_S:
            cameraLibre->deplacement ( RECULER, false );
            break;
        case Qt::Key_Q:
            cameraLibre->deplacement ( GAUCHE, false );
            break;
        case Qt::Key_D:
            cameraLibre->deplacement ( DROITE, false );
            break;
        case Qt::Key_Control:
            qDebug() << "Debout";
            cameraLibre->deplacement ( ACCROUPI, false );
            break;
        case Qt::Key_Space:
            //qDebug() << "Space";
            cameraLibre->deplacement ( SAUT, false );
            break;
        case Qt::Key_N:
        {
            if(!event->isAutoRepeat()){
               vuePrincipal->g_model.clearAnimation();
               vuePrincipal->g_model.setIsWalking(false);
            }

                break;
        }
        break;

    }
}
