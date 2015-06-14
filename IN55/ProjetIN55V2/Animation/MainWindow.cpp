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
    hasMoved = false;

    mouseTracked = true;

    anti_repetition = false;

    QVector3D orientation;

    QVector3D cibleCamera;
    float vitesseCameraLibre = 0.25;
    float sensivity = 0.1;

    QVector3D positionCamera;

    positionCamera.setX(2.78839 );
    positionCamera.setY(-180.552);
    positionCamera.setZ(70);

    orientation.setX(0);
    orientation.setY(0);
    orientation.setZ(0);

    cibleCamera.setX(0);
    cibleCamera.setY(0);
    cibleCamera.setZ(50);


    //de même on crée la camera libre
    cameraLibre = new CameraLibre(positionCamera, cibleCamera, orientation, vitesseCameraLibre, sensivity, hasMoved);

    QDesktopWidget widget;
    mainScreenSize = widget.availableGeometry(widget.primaryScreen());

    cibleCamera = cameraLibre->getCibleCamera();


    ////////////////////CREATION DE LA GUI///////////////////////////////////////////

    renderWidget = new OpenGLWidget (this, cameraLibre, positionCamera, cibleCamera);

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
    renderWidget->setSizePolicy(spLeft);

    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(1);
    boutonAnim->setSizePolicy(spRight);

    layout->addWidget(renderWidget);
    layout->addWidget(panneauBoutons);

    panneauGlobal->setLayout(layout);


    setCentralWidget(panneauGlobal);


    timerApplication = new QTimer(this);
    connect(timerApplication, SIGNAL(timeout()), this, SLOT(cycleTimer()));

    timerFPS = new QTimer(this);

    lancerApplication();

   // this->setMouseTracking(true);
        renderWidget->setMouseTracking(true);


}

void MainWindow::handleBoutonAnimation()
{
    renderWidget->g_model.loadAnim("data/animations/monster.md5anim");
    renderWidget->g_model.getAnimation().setContinuous(true);
}

void MainWindow::handleBoutonAnimationArret()
{
    renderWidget->g_model.clearAnimation();
    renderWidget->g_model.setIsWalking(false);
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

    renderWidget->updateGL();
}

void MainWindow::mouseMoveEvent ( QMouseEvent *event )
{
  cameraLibre->hasMoved = true;

    if (!anti_repetition)//on verifie que ce n'est pas la fonction qui se rappelle elle meme (avec setPos) et que la souris est sur le bon widget
    {
        float xrel = (renderWidget->width() / 2 - event->x());
        float yrel = ( renderWidget->height() / 2 - event->y());

        cameraLibre->mouvementCameraSouris ( xrel, yrel );
        QPoint pos(renderWidget->width() / 2, renderWidget->height() / 2);
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
    float vitesseCameraLibre = cameraLibre->getVitesse();

    if ( event->delta() >= 0 )
    {
        vitesseCameraLibre += 0.5;
        cameraLibre->setVitesse(vitesseCameraLibre);
    }
    else
    {
        vitesseCameraLibre -= 0.1;
        if (vitesseCameraLibre < 0)
        {
            vitesseCameraLibre = 0;
        }
        cameraLibre->setVitesse(vitesseCameraLibre);
    }
    qDebug() << "Vitesse =" << vitesseCameraLibre;
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
      case Qt::Key_F2:
                      mouseTracked = !mouseTracked;
                      this->setMouseTracking(mouseTracked);
                      renderWidget->setMouseTracking(mouseTracked);
                      if(!mouseTracked)
                          QApplication::setOverrideCursor( QCursor());
                      else
                          QApplication::setOverrideCursor( QCursor( Qt::BlankCursor ));
                  break;

    case Qt::Key_N:
    {
        if (!event->isAutoRepeat())
        {
            renderWidget->g_model.loadAnim("Meshs/boarman/doom.md5anim");
            renderWidget->g_model.getAnimation().setContinuous(true);
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
            renderWidget->g_model.clearAnimation();
            renderWidget->g_model.setIsWalking(false);
        }

        break;
    }
    break;

    }
}
