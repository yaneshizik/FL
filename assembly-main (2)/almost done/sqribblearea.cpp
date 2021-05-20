#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif

#include <iostream>
#include <QFile>

#include "scribblearea.h"
#include "circle.h"
#include "arrow.h"
#include "windows.h"



ScribbleArea::ScribbleArea(QWidget *parent)
    : QWidget(parent)
{
    // Roots the widget to the top left even if resized
    setAttribute(Qt::WA_StaticContents);

    // Set defaults for the monitored variables
    modified = false;
    scribbling = false;
}

circle Circle;
arrow Arrow;

bool ScribbleArea::saveImage(const QString &fileName)
{
    // Created to hold the image
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}


void ScribbleArea::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = false;
    update();
}

void ScribbleArea::clearScreen()
{
    clearImage();

    Arrow.clearArrows();

    Circle.clearCircles();

     //QFile file(QDir::currentPath()+"/text.txt");
     QFile file("../../../text.txt");
     file.open(QIODevice::WriteOnly);
     file.close();
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        Circle.setCircleLastPoint(event->pos());
        Arrow.setArrowFirstPoint(event->pos());
        scribbling = true;
        if(Circle.ifCircle){
            Circle.mousePressEventCircle();
            Sleep(500);
        }
        if(Arrow.ifArrow){
            Arrow.addBeginPointArrow();
            //Arrow.mousePressEventArrow();
        }
    }

    /*if (event->button() == Qt::RightButton) {
        Circle.setCircleLastPoint(event->pos());
        Arrow.setArrowLastPoint(event->pos());
    }*/
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if(Circle.ifCircle && Circle.ifMarkCircle() ) {

        if(event->buttons() & Qt::LeftButton){
            Circle.changeSizeCircle(event->pos());
        }

        if(event->buttons() & Qt::RightButton){
            Circle.changePosCircle(event->pos());
        }
    }
    else if (((event->buttons() & Qt::LeftButton) && scribbling) && Arrow.ifArrow) {
        drawLineTo(event->pos());
    }
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->button() == Qt::LeftButton && scribbling && Circle.ifCircle) && !Circle.ifMarkCircle()) {
        drawLineTo(event->pos());
        scribbling = false;
    }

    if ((event->button() == Qt::LeftButton && scribbling) && Arrow.ifArrow) {
        drawLineTo(event->pos());
        Arrow.addEndPointArrow(event->pos());
        scribbling = false;
    }
    redraw();
}

void ScribbleArea::mouseDoubleClickEvent(QMouseEvent *event) {
/*    if (event->button() == Qt::LeftButton && Circle.ifCircle) {
        QPainter painter(this);
        painter.setBrush(Qt::white);
        painter.drawEllipse(event->pos(), 10, 10);
    }
    paintEvent();
*/}

void ScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void ScribbleArea::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void ScribbleArea::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);

    painter.setPen(QPen(Arrow.getArrowPenColor(), Arrow.getArrowPenWidth(), Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    painter.drawLine(Arrow.getArrowLastPoint(), endPoint);

    //modified = true;

    Arrow.setArrowLastPoint(endPoint);
}

void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void ScribbleArea::clickedCircleButton(){
    if(Circle.ifCircle) {Circle.ifCircle = false;}
    else { Circle.ifCircle = true; Arrow.ifArrow = false;}
}

void ScribbleArea::clickedArrowButton(){
    if(Arrow.ifArrow) {Arrow.ifArrow = false;}
    else { Arrow.ifArrow = true; Circle.ifCircle = false;}

}

void ScribbleArea::clickedDeleteButton()
{
/*    circle->setAutoExclusive(false);
    circle->setChecked(false);
    circle->setAutoExclusive(true);
    arrow->setAutoExclusive(false);
    arrow->setChecked(false);
    arrow->setAutoExclusive(true);
*/

    //Circle.deleteCircle();
    if (Circle.ifMarkCircle()) {
        Circle.listCircles.erase(Circle.listCircles.begin() + Circle.numCurCircle);
        Arrow.checkNearArrow(Circle.listRect);
        Circle.listRect.erase(Circle.listRect.begin());
        modified = true;
    }
    redraw();

}

void ScribbleArea::redraw(){
    clearImage();
    QPainter painter(&image);
    painter.setPen(QPen(Arrow.getArrowPenColor(), Arrow.getArrowPenWidth()+1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setRenderHint(QPainter::Antialiasing, true);
    int size = Arrow.listArrows.size();
    for(int i=0;i<size;i++){
        painter.drawLine(Arrow.listArrows[i].first, Arrow.listArrows[i].second);
    }

    painter.setPen(QPen(Circle.getCirclePenColor(), Circle.getCirclePenWidth()+1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Circle.getCircleBrushColor());
    size = Circle.listCircles.size();
    for(int i=0; i<size; i++){
        painter.drawEllipse(Circle.listCircles[i].first, Circle.listCircles[i].second, Circle.listCircles[i].second);
    }

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(QBrush (Qt::transparent));
    size = Circle.listRect.size();
    if(size != 0) {
        painter.drawRect(Circle.listRect[0].first.x(), Circle.listRect[0].first.y(), Circle.listRect[0].second, Circle.listRect[0].second);
    }

    //QFile file(QDir::currentPath()+"/text.txt");
    QFile file("../../../text.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        //circle pen color, arrow color, circle brush color, circle width, arrow width
        QString str = Circle.getCirclePenColor().name()+"|"+Circle.getCircleBrushColor().name()+"|"
                +QString::number(Circle.getCirclePenWidth())+"|"+Arrow.getArrowPenColor().name()+"|"
                +QString::number(Arrow.getArrowPenWidth())+"\n";
        file.write(str.toUtf8());

        int size = Arrow.listArrows.size();
        for(int i=0; i<size; i++){
            //if arrow length is not 0
           if (Arrow.listArrows[i].first.x() != Arrow.listArrows[i].second.x() or Arrow.listArrows[i].first.y() != Arrow.listArrows[i].second.y()) {
                QString str = "0|" + QString::number(Arrow.listArrows[i].first.x())+"|"
                    + QString::number(Arrow.listArrows[i].first.y()) + "|"
                    + QString::number(Arrow.listArrows[i].second.x())+"|"
                    + QString::number(Arrow.listArrows[i].second.y()) + "\n";
                file.write(str.toUtf8());
            }
        }

        //file.write(QString::number(Arrow.numCurArrow).toUtf8());

        size = Circle.listCircles.size();
        for(int i=0;i<size; i++){
        QString str = "1|" + QString::number(Circle.listCircles[i].first.x())+"|"
                    + QString::number(Circle.listCircles[i].first.y()) + "|"
                     + QString::number(Circle.listCircles[i].second) + "\n";
        file.write(str.toUtf8());
        }

        //file.write(QString::number(Circle.numCurCircle).toUtf8());

        /*size = Circle.listRect.size();
        if(size != 0){
            QString str = QString::number(Circle.listRect[0].first.x())+" "
                        + QString::number(Circle.listRect[0].first.y()) + " "
                         + QString::number(Circle.listRect[0].second) + "\n";
            file.write(str.toUtf8());
        }*/

        file.close();
    }
    modified = true;
}
