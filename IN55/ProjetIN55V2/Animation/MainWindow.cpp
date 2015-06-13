#include "MainWindow.h"
#include <QThread>
#include <QPushButton>
#include <QHBoxLayout>

#define AVANCER 0
#define RECULER 1
#define GAUCHE 2
#define DROITE 3
#define MONTER 4
#define DESCENDRE 5

using namespace std;

/////////////////////////////// PUBLIC ///////////////////////////////////////

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setWindowTitle("Projet IN55 - Animation");

    fullscreen = false;

    mouseTracked = true;

    anti_repetition = false;

    QVector3D m_orientationObjet;

    QVector3D m_cibleCamera;
    float m_vitessecameraLibre = 0.25;
    float sensivity = 0.1;

    QVector3D m_positionCamera;

    m_positionCamera.setX(2.78839 );
    m_positionCamera.setY(-180.552);
    m_positionCamera.setZ(70);

    m_orientationObjet.setX(0);
    m_orientationObjet.setY(0);
    m_orientationObjet.setZ(0);

    m_cibleCamera.setX(0);
    m_cibleCamera.setY(0);
    m_cibleCamera.setZ(0);


    //de même on crée la camera libre
    cameraLibre = new CameraLibre(m_positionCamera, m_cibleCamera, m_orientationObjet, m_vitessecameraLibre, sensivity);

    QDesktopWidget widget;
    mainScreenSize = widget.availableGeometry(widget.primaryScreen());


    ////////////////////CREATION DE LA GUI///////////////////////////////////////////

    vuePrincipal = new OpenGLWidget (this, cameraLibre, m_positionCamera, m_cibleCamera);

    QWidget *panneauGlobal = new QWidget();

    QPushButton *boutonAnim = new QPushButton("Animation");
    QPushButton *boutonAnimArret = new QPushButton("Arrêt");
    QPushButton *boutonPause = new QPushButton("Pause");
    QPushButton *boutonMonter = new QPushButton("Monter");
    QPushButton *boutonDescendre = new QPushButton("Descendre");


    // On associe des actions aux clics des différents boutons
    connect(boutonAnim, SIGNAL (released()), this, SLOT (handleBoutonAnimation()));
    connect(boutonAnimArret, SIGNAL (released()), this, SLOT (handleBoutonAnimationArret()));
    connect(boutonPause, SIGNAL (released()), this, SLOT (handleBoutonPause()));
    connect(boutonMonter, SIGNAL (pressed()), this, SLOT (handleBoutonMonter()));
    connect(boutonDescendre, SIGNAL (pressed()), this, SLOT (handleBoutonDescendre()));
    connect(boutonMonter, SIGNAL (released()), this, SLOT (handleBoutonStop()));
    connect(boutonDescendre, SIGNAL (released()), this, SLOT (handleBoutonStop()));

    //Agencement des boutons dans la fenêtre
    QHBoxLayout *layout = new QHBoxLayout;
    QVBoxLayout *boutonLayout = new QVBoxLayout();

    QWidget *panneauBoutons = new QWidget();

    boutonLayout->addWidget(boutonAnim);
    boutonLayout->addWidget(boutonAnimArret);
    boutonLayout->addWidget(boutonPause);
    boutonLayout->addWidget(boutonMonter);
    boutonLayout->addWidget(boutonDescendre);

    panneauBoutons->setLayout(boutonLayout);

    QSizePolicy spLeft(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spLeft.setHorizontalStretch(3);
    vuePrincipal->setSizePolicy(spLeft);

    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(1);
    boutonAnim->setSizePolicy(spRight);

    layout->addWidget(vuePrincipal);
    layout->addWidget(panneauBoutons);

    panneauGlobal->setLayout(layout);


    setCentralWidget(panneauGlobal);


    timerApplication = new QTimer(this);
    connect(timerApplication, SIGNAL(timeout()), this, SLOT(cycleTimer()));

    timerFPS = new QTimer(this);

    lancerApplication();

}

void MainWindow::handleBoutonAnimation()
{
    vuePrincipal->g_model.loadAnim("data/animations/monster.md5anim");
    vuePrincipal->g_model.getAnimation().setContinuous(true);
}

void MainWindow::handleBoutonAnimationArret()
{
    vuePrincipal->g_model.clearAnimation();
    vuePrincipal->g_model.setIsWalking(false);
}

void MainWindow::handleBoutonPause()
{
    if ( !enPause )
    {
        enPause = true;
        stopperApplication();
    }
    else
    {
        enPause = false;
        lancerApplication();
    }
}

void MainWindow::handleBoutonMonter()
{
    cameraLibre->deplacement ( MONTER, true );
}

void MainWindow::handleBoutonDescendre()
{
    cameraLibre->deplacement ( DESCENDRE, true );
}

void MainWindow::handleBoutonStop()
{
    cameraLibre->deplacement(MONTER, false);
    cameraLibre->deplacement(DESCENDRE, false);
}



MainWindow::~MainWindow()
{

}

void MainWindow::lancerApplication()
{
    timerApplication->start(20);
    timerFPS->start(1000);
}


void MainWindow::stopperApplication()
{
    timerApplication->stop();
    timerFPS->stop();
}

void MainWindow::cycleTimer()
{
    numCycle++;
    cameraLibre->Animate();

    vuePrincipal->updateGL();
}

void MainWindow::mouseMoveEvent ( QMouseEvent *event )
{
    if (!anti_repetition)//on verifie que ce n'est pas la fonction qui se rappelle elle meme (avec setPos) et que la souris est sur le bon widget
    {
        int xrel = (width() / 2 - event->x());
        int yrel = ( height() / 2 - event->y());

        cameraLibre->mouvementCameraSouris ( xrel, yrel );
        QPoint pos(width() / 2, height() / 2);
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
        cameraLibre->setVitesse(m_vitessecameraLibre);
    }
    else
    {
        m_vitessecameraLibre -= 0.1;
        if (m_vitessecameraLibre < 0)
        {
            m_vitessecameraLibre = 0;
        }
        cameraLibre->setVitesse(m_vitessecameraLibre);
    }
    qDebug() << "Vitesse =" << m_vitessecameraLibre;
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
            stopperApplication();
        }
        else
        {
            enPause = false;
            lancerApplication();
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
        // qDebug() << "Descendre";
        cameraLibre->deplacement ( DESCENDRE, true );
        break;
    case Qt::Key_Space:
        //qDebug() << "Monter";
        cameraLibre->deplacement ( MONTER, true );
        break;
    case Qt::Key_Shift:
        qDebug() << "Pos = " << _posi.x() << _posi.y() << _posi.z();
        break;
    case Qt::Key_F1:
        if (fullscreen)
        {
            setWindowState(Qt::WindowNoState);
            fullscreen = false;
            qDebug() << "+ Window mode";
        }
        else
        {
            setWindowState(Qt::WindowFullScreen);
            fullscreen = true;
            qDebug() << "+ Full screen";
        }
        break;

    case Qt::Key_N:
    {
        if (!event->isAutoRepeat())
        {
            vuePrincipal->g_model.loadAnim("Meshs/boarman/doom.md5anim");
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
        cameraLibre->deplacement ( DESCENDRE, false );
        break;
    case Qt::Key_Space:
        //qDebug() << "Space";
        cameraLibre->deplacement ( MONTER, false );
        break;
    case Qt::Key_N:
    {
        if (!event->isAutoRepeat()) {
            vuePrincipal->g_model.clearAnimation();
            vuePrincipal->g_model.setIsWalking(false);
        }

        break;
    }
    break;

    }
}
