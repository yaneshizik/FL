#include <QtWidgets>

#include "mainwindow.h"
#include "scribblearea.h"
#include "ui_mainwindow.h"

// MainWindow constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);

    //createActions();
    //createMenus();

    setWindowTitle(tr("FLHelper"));

    resize(500, 500);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}
