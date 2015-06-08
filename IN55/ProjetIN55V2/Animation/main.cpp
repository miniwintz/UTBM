#include "MainWindow.h"
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qApp->processEvents();

    MainWindow w;
    w.show();

    return a.exec();
}
