#pragma once
#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <vector>
#include <utility>
#include <QRadioButton>

class ScribbleArea : public QWidget
{
    Q_OBJECT

public:
    ScribbleArea(QWidget *parent = 0);

    bool saveImage(const QString &fileName);
    void redraw();

    bool isModified() const { return modified; }

public slots:

    void clearScreen();
    void clickedCircleButton();
    void clickedArrowButton();
    void clickedDeleteButton();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    void clearImage();

    bool modified;
    bool scribbling;
    QImage image;
};

#endif // SCRIBBLEAREA_H
