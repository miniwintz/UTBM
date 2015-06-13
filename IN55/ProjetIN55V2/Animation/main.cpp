#include "MainWindow.h"
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qApp->processEvents();

    MainWindow w;

    QDesktopWidget widget;
    QRect mainScreenSize = widget.availableGeometry(widget.primaryScreen());


    w.setGeometry(30, 30, (float)(mainScreenSize.width()) / 1.5, (float)(mainScreenSize.height()) / 1.5);
    w.show();

    return a.exec();
}
