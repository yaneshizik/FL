#include "mainwindow.h"
#include "appearance.h"
//#include "menu.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Appearance window;

    window.show();
    return app.exec();
}
