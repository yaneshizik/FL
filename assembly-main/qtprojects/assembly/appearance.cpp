#pragma once
#include "appearance.h"
#include "scribblearea.h"
#include <iostream>
#include "tex.h"


Appearance::Appearance(QWidget *parent): QMainWindow(parent){

    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);

    createMenus();
    createTools();
    resize(500,500);
    setWindowTitle(QDir::currentPath()+"/text.txt");
}

void Appearance::createMenus(){
    quit = new QAction("&Quit", this);
    connect(quit, &QAction::triggered, qApp, &QApplication::quit);

    clearScreenAct = new QAction("C&learScreen", this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()), scribbleArea, SLOT(clearScreen()));

    circlePenColorAct = new QAction("CirclePenColor",this);
    connect(circlePenColorAct, SIGNAL(triggered()), this, SLOT(circlePenColor()));

    circleWidthAct = new QAction("CircleWidth",this);

    arrowPenColorAct = new QAction("ArrowPenColor",this);
    connect(arrowPenColorAct, SIGNAL(triggered()), this, SLOT(arrowPenColor()));


    arrowWidthAct = new QAction("ArrowWidth",this);

    saveAct = new QAction("Save as image", this);
    saveAct->setShortcut(tr("Ctrl+Shift+S"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

    saveToTexAct = new QAction("SaveToTex", this);
    saveToTexAct->setShortcut(tr("Ctrl+Shift+T"));
    connect(saveToTexAct, SIGNAL(triggered()), qApp, SLOT());

    file = new QMenu(tr("File"),this);
    file->addAction(saveAct);
    file->addAction(saveToTexAct);
    file->addAction(quit);

    optionMenu = new QMenu(tr("Options"),this);
    optionMenu->addAction(circlePenColorAct);
    optionMenu->addAction(circleWidthAct);
    optionMenu->addAction(arrowPenColorAct);
    optionMenu->addAction(arrowWidthAct);




    menuBar()->addMenu(file);
    menuBar()->addMenu(optionMenu);
    menuBar()->addSeparator();
    menuBar()->addAction(clearScreenAct);

}

void Appearance::createTools(){

    circle = new QRadioButton(tr("&Circle"),this);
    circle->setCheckable(true);
    connect(circle, SIGNAL(clicked()), scribbleArea, SLOT(clickedCircleButton()));
//    connect(circle, SIGNAL(toggled()), this, SLOT(arrow->setDown(false)));

    arrow = new QRadioButton(tr("&Arrow"),this);
    arrow->setCheckable(true);
    connect(arrow, SIGNAL(clicked()), scribbleArea, SLOT(clickedArrowButton()));
//    connect(arrow, SIGNAL(preassured()), this, SLOT(circle->setDown(false)));

//    knopka = new QPushButton(tr("knopka"), this);
//    connect(knopka, SIGNAL(clicked))



    deleteBut = new QPushButton(tr("&Delete"),this);
    deleteBut->setCheckable(false);
    deleteBut->setShortcut(tr("CTRL+D"));
    deleteBut->setChecked(false);
    connect(deleteBut, SIGNAL(clicked()), scribbleArea, SLOT(clickedDeleteButton()));

    toolbar = addToolBar("main toolbar");
    toolbar->addWidget(circle);
    toolbar->addWidget(arrow);
//    toolbar->addWidget(knopka);
    toolbar->addWidget(deleteBut);
}


void Appearance::circlePenColor()
{
    QColor newColor = QColorDialog::getColor(scribbleArea->circlePenColor());

    if (newColor.isValid())
        scribbleArea->setCirclePenColor(newColor);
}

void Appearance::arrowPenColor()
{
    QColor newColor = QColorDialog::getColor(scribbleArea->arrowPenColor());

    if (newColor.isValid())
        scribbleArea->setArrowPenColor(newColor);
}



bool Appearance::saveFile()
{
    QString initialPath = QDir::currentPath() + "/untitled.";

    QString saveFileName = QFileDialog::getSaveFileName(this,  tr("Save as"), initialPath, tr("PNG(*.png);; TIFF(*.tiff *.tif);; JPEG(*.jpg *.jpeg);;All files(*)"));
    int pos = saveFileName.lastIndexOf('.');
    if (pos >= 0){
        return scribbleArea->saveImage(saveFileName);
    }
    else {
         return false;
    }
}


