#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "OpenGLWidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void cycleTimerJeu();

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



    QTimer *timerJeu;
    QTimer *timerFPS;

    bool anti_repetition;
    bool fullscreen;
    bool mouseTracked;

    QPoint oldPosSouris;


};

#endif // MAINWINDOW_H
