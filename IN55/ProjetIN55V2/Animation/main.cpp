#include "MainWindow.h"
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qApp->processEvents();

    MainWindow w;
    w.setGeometry(30,30,800,600);
    w.show();

    return a.exec();
}
