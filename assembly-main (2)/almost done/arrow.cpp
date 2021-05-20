#include "arrow.h"
#include <QApplication>


arrow::arrow(QObject *parent)
    : QObject(parent)
{
    ArrowPenColor = Qt::black;
    ifArrow = false;
    numCurArrow=-1;
    ArrowPenWidth = 1;
}

QColor arrow::getArrowPenColor() {
    return ArrowPenColor;
}

QPoint arrow::getArrowLastPoint() {
    return ArrowLastPoint;
}

int arrow::getArrowPenWidth() {
    return ArrowPenWidth;
}

QPoint arrow::getArrowFirstPoint() {
    return ArrowFirstPoint;
}

void arrow::setArrowPenColor(const QColor &newColor)
{
    ArrowPenColor = newColor;
}

void arrow::setArrowLastPoint(const QPoint &newPoint)
{
    ArrowLastPoint = newPoint;
}

void arrow::setArrowFirstPoint(const QPoint &newPoint)
{
    ArrowFirstPoint = newPoint;
}

void arrow::setArrowPenWidth(const int &newWidth) {
    ArrowPenWidth = newWidth;
}

void arrow::clearArrows() {
    int size = listArrows.size();
    for(int i=size-1; i>=0; i--) {
        listArrows.erase(listArrows.begin()+i);
    }
    numCurArrow = -1;
}

void arrow::deleteArrow(int &i){
    listArrows.erase(listArrows.begin()+i);
}

void arrow::addBeginPointArrow() {
    QPoint point;
    point.setX(0);
    point.setY(0);
    listArrows.push_back({getArrowFirstPoint(),point});
    numCurArrow = listArrows.size()-1;
}

void arrow::addEndPointArrow(const QPoint &endPoint) {
    listArrows[numCurArrow].second = endPoint;
}

void arrow::checkNearArrow(std::vector<std::pair<QPoint,int>> &rect){
    int size = listArrows.size();
    if(size > 0){
        for(int i = 0; i < size; i++){
            if (((listArrows[i].first.x() > rect[0].first.x()) && (listArrows[i].first.x() < rect[0].first.x() + rect[0].second)
                 && (listArrows[i].first.y() > rect[0].first.y()) && (listArrows[i].first.y() < rect[0].first.y() + rect[0].second))
                    || ((listArrows[i].second.x() > rect[0].first.x()) && (listArrows[i].second.x() < rect[0].first.x() + rect[0].second)
                        && (listArrows[i].second.y() > rect[0].first.y()) && (listArrows[i].second.y() < rect[0].first.y() + rect[0].second))){
                deleteArrow(numCurArrow);
            }
        }
    }
}


