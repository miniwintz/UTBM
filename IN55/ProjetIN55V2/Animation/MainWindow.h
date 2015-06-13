#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "OpenGLWidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void lancerApplication();
    void stopperApplication();
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent ( QKeyEvent * event );

    bool enPause;
    int numCycle;

    QRect mainScreenSize;

    OpenGLWidget *vuePrincipal;
    CameraLibre *cameraLibre;

    QTimer *timerApplication;
    QTimer *timerFPS;

    bool anti_repetition;
    bool fullscreen;
    bool mouseTracked;

    QPoint oldPosSouris;

private slots:
    void handleBoutonAnimation();
    void handleBoutonAnimationArret();
    void handleBoutonPause();
    void handleBoutonMonter();
    void handleBoutonDescendre();
    void handleBoutonStop();
    void cycleTimer();


};

#endif // MAINWINDOW_H
