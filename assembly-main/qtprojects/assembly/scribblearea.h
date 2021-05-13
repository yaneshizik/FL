#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#pragma once
#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <vector>
#include <utility>

class ScribbleArea : public QWidget
{
    Q_OBJECT

public:
    ScribbleArea(QWidget *parent = 0);

    void setCirclePenColor(const QColor &newColor);
    void setArrowPenColor(const QColor &newColor);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    QColor circlePenColor() const { return myCirclePenColor;}
    QColor arrowPenColor() const { return myArrowPenColor;}
    int penWidth() const { return myPenWidth; }
    bool saveImage(const QString &fileName);


public slots:

    void clearScreen();
    void print();
    void clickedCircleButton();
    void clickedArrowButton();
    void clickedDeleteButton();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void drawNewCircle(const QPoint &endPoint);
    void markCircle(const std::vector<int> &parametrs);
    void resizeImage(QImage *image, const QSize &newSize);
    void redraw();
    void disMarkCircle();

    void clearImage();
    void changeSizeCircle(const QPoint &endPoint);
    void changePosCircle(const QPoint &endPoint);
    void addBeginPointArrow();
    void addEndPointArrow(const QPoint &endPoint);
    std::vector<int> ifEmptyCircle(const QPoint &endPoint);
    int numCurCircle;
    int numCurArrow;

    void deleteObject();
    std::vector<std::pair<QPoint,int>> listCircles;
    std::vector<std::pair<QPoint,int>> listRect;
    std::vector<std::pair<QPoint,QPoint>> listArrows;
    std::vector<int> circleParametrs;

    bool ifCircle;
    bool ifArrow;
    bool ifMarkCircle();

    bool modified;

    bool scribbling;

    int myPenWidth;

    QColor myArrowPenColor;
    QColor myCirclePenColor;

    QImage image;

    QPoint lastPoint;
};

#endif // SCRIBBLEAREA_H
