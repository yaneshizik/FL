#pragma once
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

ScribbleArea::ScribbleArea(QWidget *parent)
    : QWidget(parent)
{
    // Roots the widget to the top left even if resized
    setAttribute(Qt::WA_StaticContents);

    // Set defaults for the monitored variables
    modified = false;
    scribbling = false;
    myPenWidth = 1;
    myArrowPenColor = Qt::blue;

    myCirclePenColor= Qt::yellow;

    ifCircle = false;
    ifArrow = false;

    numCurArrow=-1;
    numCurCircle=-1;

    std::vector<int> circleParametrs;
}


// Used to change the pen width
void ScribbleArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

// Color the image area with white
void ScribbleArea::clearImage()
{
    image.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

void ScribbleArea::clearScreen(){
    clearImage();

    int size = listArrows.size();
    for(int i=size-1; i>=0; i--){
        listArrows.erase(listArrows.begin()+i);
    }

    size = listCircles.size();
        for(int i=size-1; i>=0; i--){
            listCircles.erase(listCircles.begin()+i);
        }

     size = listRect.size();
     if (size>0){
        listRect.erase(listRect.begin());
     }

     QFile file(QDir::currentPath()+"/text.txt");
     file.open(QIODevice::WriteOnly);
     file.close();

     numCurCircle = -1;
     numCurArrow = -1;


}

// If a mouse button is pressed check if it was the
// left button and if so store the current position
// Set that we are currently drawing
void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
        if(ifCircle){
            circleParametrs = ifEmptyCircle(lastPoint);
            if(circleParametrs[0]==0 && !ifMarkCircle())drawNewCircle(lastPoint);
            else if(!ifMarkCircle()) markCircle(circleParametrs);
            else if(circleParametrs[0]==0) disMarkCircle();
        }
        if(ifArrow){
            addBeginPointArrow();
        }

    }
    if (event->button() == Qt::RightButton) {
        lastPoint = event->pos();
    }
}

// When the mouse moves if the left button is clicked
// we call the drawline function which draws a line
// from the last position to the current
void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if(ifCircle && ifMarkCircle() ) {

        if(event->buttons() & Qt::LeftButton){
            changeSizeCircle(event->pos());
        }

        if(event->buttons() & Qt::RightButton){
            changePosCircle(event->pos());
        }
    }
    else if (((event->buttons() & Qt::LeftButton) && scribbling) && ifArrow)
        drawLineTo(event->pos());
}

// If the button is released we set variables to stop drawing
void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->button() == Qt::LeftButton && scribbling && ifCircle) && !ifMarkCircle()) {
        drawLineTo(event->pos());
        scribbling = false;
    }

    if ((event->button() == Qt::LeftButton && scribbling) && ifArrow) {
        drawLineTo(event->pos());
        addEndPointArrow(event->pos());
        scribbling = false;
    }
    redraw();
}

// QPainter provides functions to draw on the widget
// The QPaintEvent is sent to widgets that need to
// update themselves
void ScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Returns the rectangle that needs to be updated
    QRect dirtyRect = event->rect();

    // Draws the rectangle where the image needs to
    // be updated
    painter.drawImage(dirtyRect, image, dirtyRect);
}

// Resize the image to slightly larger then the main window
// to cut down on the need to resize the image
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
    // Used to draw on the widget
    QPainter painter(&image);

    // Set the current settings for the pen
    painter.setPen(QPen(myArrowPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));

    // Draw a line from the last registered point to the current
    painter.drawLine(lastPoint, endPoint);

    // Set that the image hasn't been saved
    modified = true;

    int rad = (myPenWidth / 2) + 2;

    // Call to update the rectangular space where we drew
    update(QRect(lastPoint, endPoint).normalized()
                                     .adjusted(-rad, -rad, +rad, +rad));

    // Update the last position where we left off drawing
    lastPoint = endPoint;
}

void ScribbleArea::drawNewCircle(const QPoint &endPoint){
    //QPainter painter(&image);
    //painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    int radius = 25;
    //painter.drawEllipse(endPoint, radius,radius);
    std::pair<QPoint,int> oneMore(endPoint,radius);
    listCircles.push_back(oneMore);
    modified = true;
    redraw();
}

// When the app is resized create a new image using
// the changes made to the image
void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
{
    // Check if we need to redraw the image
    if (image->size() == newSize)
        return;

    // Create a new image to display and fill it with white
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));

    // Draw the image
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

// Print the image
void ScribbleArea::print()
{
    // Check for print dialog availability
#if QT_CONFIG(printdialog)

    // Can be used to print
    QPrinter printer(QPrinter::HighResolution);

    // Open printer dialog and print if asked
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
#endif // QT_CONFIG(printdialog)
}


void ScribbleArea::clickedCircleButton(){
    if(ifCircle) {ifCircle = false; myArrowPenColor = Qt::blue;}
    else { ifCircle = true; myArrowPenColor = Qt::yellow; ifArrow = false;}
}
void ScribbleArea::clickedArrowButton(){
    if(ifArrow) {ifArrow = false; myArrowPenColor = Qt::blue;}

    else { ifArrow = true; myArrowPenColor = Qt::green; ifCircle = false;}

}

void ScribbleArea::clickedDeleteButton(){
    deleteObject();
}

void ScribbleArea::deleteObject(){
    if (ifMarkCircle()) {
        listCircles.erase(listCircles.begin() + numCurCircle);
        listRect.erase(listRect.begin());
    }
     redraw();
}

void ScribbleArea::markCircle(const std::vector<int> &parametrs){
    //QPainter painter(&image);
    //painter.setPen(QPen(Qt::black, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    int radius = parametrs[3];
    //painter.drawEllipse(parametrs[1],parametrs[2],parametrs[3],parametrs[3]);
    //painter.drawRect(parametrs[1]-radius,parametrs[2]-radius,2*radius,2*radius);
    QPoint point;
    point.setX(parametrs[1]-radius);
    point.setY(parametrs[2]-radius);
    listRect.push_back({point,2*radius});
    modified = true;
    redraw();
}

std::vector<int> ScribbleArea::ifEmptyCircle(const QPoint &endPoint){
    int size = listCircles.size();
    std::vector<int> parametrs={0,0,0,0};
    if(size==0) return {0,0,0,0};
    for(int i=0; i<size; i++){
        int a = endPoint.x()-listCircles[i].first.x();
        int b = endPoint.y()-listCircles[i].first.y();
        int res = a*a + b*b - listCircles[i].second*listCircles[i].second;
        numCurCircle= i;
        if(res < 0) return {1,listCircles[i].first.x(),listCircles[i].first.y(),listCircles[i].second};
    }

    return parametrs;
}

void ScribbleArea::redraw(){
    clearImage();
    QPainter painter(&image);
    painter.setPen(QPen(Qt::green, myPenWidth+1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    int size = listArrows.size();
    for(int i=0;i<size;i++){
        painter.drawLine(listArrows[i].first,listArrows[i].second);
    }

    painter.setPen(QPen(myCirclePenColor, myPenWidth+1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(QBrush (Qt::white));
    size = listCircles.size();
    for(int i=0; i<size; i++){
        painter.drawEllipse(listCircles[i].first,listCircles[i].second,listCircles[i].second);
    }

    painter.setPen(QPen(Qt::black, myPenWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(QBrush (Qt::transparent));
    size = listRect.size();
    if(size != 0) {
        painter.drawRect(listRect[0].first.x(), listRect[0].first.y(), listRect[0].second, listRect[0].second);
    }

    QFile file(QDir::currentPath()+"/text.txt");
    if (file.open(QIODevice::WriteOnly))
    {
        int size = listArrows.size();
        for(int i=0; i<size; i++){
        QString str = QString::number(listArrows[i].first.x())+" "
                    + QString::number(listArrows[i].first.y()) + " "
                    + QString::number(listArrows[i].second.x())+" "
                    + QString::number(listArrows[i].second.y()) + "\n";
        file.write(str.toUtf8());
        }

        file.write(QString::number(numCurArrow).toUtf8());

        size = listCircles.size();
        for(int i=0;i<size; i++){
        QString str = QString::number(listCircles[i].first.x())+" "
                    + QString::number(listCircles[i].first.y()) + " "
                     + QString::number(listCircles[i].second) + "\n";
        file.write(str.toUtf8());
        }

        file.write(QString::number(numCurCircle).toUtf8());

        size = listRect.size();
        if(size != 0){
            QString str = QString::number(listRect[0].first.x())+" "
                        + QString::number(listRect[0].first.y()) + " "
                         + QString::number(listRect[0].second) + "\n";
            file.write(str.toUtf8());
        }

        file.close();
    }

}

bool ScribbleArea::ifMarkCircle(){
    if (listRect.size() == 0) return false;
    else return true;
}

void ScribbleArea::disMarkCircle(){
    listRect.erase(listRect.begin());
    numCurCircle=-1;
    redraw();
}

void ScribbleArea::changeSizeCircle(const QPoint &endPoint){
    int a = lastPoint.x()-endPoint.x();
    int b = lastPoint.y()-endPoint.y();
    int radius = a*a + b*b;
    radius = sqrt(radius);
    listCircles[numCurCircle].second=radius;
    QPoint point;
    point.setX(listCircles[numCurCircle].first.x()-listCircles[numCurCircle].second);
    point.setY(listCircles[numCurCircle].first.y()-listCircles[numCurCircle].second);
    listRect[0].first = point;
    listRect[0].second = 2*listCircles[numCurCircle].second;
    redraw();

}

void ScribbleArea::changePosCircle(const QPoint &endPoint){
    listCircles[numCurCircle].first.setX(listCircles[numCurCircle].first.x() + (endPoint.x()-lastPoint.x()));
    listCircles[numCurCircle].first.setY(listCircles[numCurCircle].first.y() + (endPoint.y()-lastPoint.y()));
    QPoint point;
    point.setX(listCircles[numCurCircle].first.x()-listCircles[numCurCircle].second);
    point.setY(listCircles[numCurCircle].first.y()-listCircles[numCurCircle].second);
    listRect[0].first = point;
    redraw();
    lastPoint = endPoint;
}

void ScribbleArea::addBeginPointArrow(){
    QPoint point;
    point.setX(0);
    point.setY(0);
    listArrows.push_back({lastPoint,point});
    numCurArrow = listArrows.size()-1;

}

void ScribbleArea::addEndPointArrow(const QPoint &endPoint){
    listArrows[numCurArrow].second = endPoint;
}



void ScribbleArea::setCirclePenColor(const QColor &newColor)
{
    myCirclePenColor = newColor;
}

void ScribbleArea::setArrowPenColor(const QColor &newColor)
{
    myArrowPenColor = newColor;
}

// Save the current image
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
