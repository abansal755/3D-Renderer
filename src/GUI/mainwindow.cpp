#include "mainwindow.h"
#include "src/GUI/modelpropertieswidget.h"

#include <QApplication>

MainWindow::MainWindow(QWidget*parent):QMainWindow(parent){
    resize(800,600);

    QMenu* fileMenu=menuBar()->addMenu("File");
    QAction* exitAction=fileMenu->addAction("Exit");
    connect(exitAction,SIGNAL(triggered()),this,SLOT(exitApp()));

    hb1=new QHBoxLayout;
    vb1=new QVBoxLayout;
    central=new QWidget;
    listWidget=new ListWidget(vb1);
    glwidget=new GLWidget(listWidget);

    setCentralWidget(central);
    central->setLayout(hb1);
    hb1->addWidget(glwidget,1);
    hb1->addLayout(vb1);
    vb1->addWidget(listWidget);
}

void MainWindow::exitApp(){
    QApplication::exit(0);
}
