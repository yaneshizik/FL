#pragma once
#ifndef APPEARANCE_H
#define APPEARANCE_H

#include <QMainWindow>
#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QtWidgets>


class ScribbleArea;
class tex;

class Appearance : public QMainWindow{
    Q_OBJECT

public:
    Appearance(QWidget *parent=0);

private slots:
    void circlePenColor();
    void circleWidth();
    void circleBrushColor();
    void arrowPenColor();
    void arrowWidth();
    bool maybeSave();
    void closeEvent(QCloseEvent *event);
    bool saveFile();

private:
    void createMenus();
    void createTools();

    ScribbleArea *scribbleArea;
    tex *Tex;

    QMenu *file;
    QMenu *optionMenu;
    QAction *clearScreenAct;
    QAction *circlePenColorAct;
    QAction *circleBrushColorAct;
    QAction *circleWidthAct;
    QAction *arrowPenColorAct;
    QAction *arrowWidthAct;
    QAction *saveAct;
    QAction *saveToTexAct;
    QToolBar *toolbar;
    QRadioButton *circle;
    QRadioButton *arrow;
    QPushButton *deleteBut;

};

#endif // APPEARANCE_H
