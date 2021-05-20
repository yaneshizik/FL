#include "mainwindow.h"
#include "appearance.h"
#include "circle.h"
//#include "menu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Appearance window;

    window.setWindowIcon(QIcon("../../../myapp.ico"));

    circle Circle;

    window.show();
    return app.exec();
}
