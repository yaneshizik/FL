#include "scene.h"
#include <QApplication>
#include <QGraphicsView>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("myapp.ico"));

    Scene scene;
    QGraphicsView view(&scene);

    scene.setSceneRect(-10, -10, 500, 500);
    view.setRenderHint(QPainter::Antialiasing);

    a.setApplicationName("FL Helper");

    view.show();

    return a.exec();
}
