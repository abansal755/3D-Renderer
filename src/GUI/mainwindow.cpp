#include "mainwindow.h"
#include "src/GUI/modelpropertieswidget.h"

#include <QApplication>

MainWindow::MainWindow(QWidget*parent):QMainWindow(parent){
    resize(800,600);
    glwidget=new GLWidget;
    setCentralWidget(glwidget);

    QMenu* fileMenu=menuBar()->addMenu("File");
    QAction* exitAction=fileMenu->addAction("Exit");
    connect(exitAction,SIGNAL(triggered()),this,SLOT(exitApp()));
}

void MainWindow::exitApp(){
    QApplication::exit(0);
}
