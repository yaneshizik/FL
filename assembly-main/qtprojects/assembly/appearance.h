#ifndef APPEARANCE_H
#define APPEARANCE_H

#pragma once
#include <QMainWindow>
#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QtWidgets>
#include <QLabel>


class ScribbleArea;

class Appearance : public QMainWindow{
    Q_OBJECT

public:
    Appearance(QWidget *parent=0);

private slots:
    void circlePenColor();
    void arrowPenColor();
    bool saveFile();

private:
    void createMenus();
    void createTools();

    ScribbleArea *scribbleArea;

    QMenu *file;
    QMenu *optionMenu;
    QAction *quit;
    QAction *clearScreenAct;
    QAction *circlePenColorAct;
    QAction *circleWidthAct;
    QAction *arrowPenColorAct;
    QAction *arrowWidthAct;
    QAction *saveAct;
    QAction *saveToTexAct;
    QToolBar *toolbar;
    QRadioButton *circle;
    QRadioButton *arrow;
    QPushButton *deleteBut;
    QPushButton *knopka;
    QLabel *label;



};






#endif // APPEARANCE_H
