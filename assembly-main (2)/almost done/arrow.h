#pragma once
#ifndef ARROW_H
#define ARROW_H
#include <QApplication>
#include <QWidget>
#include <QPoint>


class arrow : public QObject
{
    Q_OBJECT
public:
    arrow(QObject *parent = 0);

    void setArrowPenColor(const QColor &newColor);
    void setArrowLastPoint(const QPoint &newPoint);
    void setArrowFirstPoint(const QPoint &newPoint);
    void setArrowPenWidth(const int &newWidth);
    void clearArrows();
    void deleteArrow(int &i);
    void addBeginPointArrow();
    void addEndPointArrow(const QPoint &endPoint);
    void mousePressEventArrow();

    QColor getArrowPenColor();
    QPoint getArrowLastPoint();
    QPoint getArrowFirstPoint();
    int getArrowPenWidth();

    int numCurArrow;
    bool ifArrow;
    bool ifMarkArrow();
    std::vector<std::pair<QPoint,QPoint>> listArrows;
    void checkNearArrow(std::vector<std::pair<QPoint,int>> &rect);
//    std::vector<std::pair<QPoint,int>> listRect;


private:
    QColor ArrowPenColor;
    QPoint ArrowLastPoint;
    QPoint ArrowFirstPoint;
    int ArrowPenWidth;
    void markArrow(const std::vector<int> &parametrs);
    void disMarkArrow();
};

#endif // ARROW_H
