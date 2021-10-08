#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){
    resize(800,600);
    glwidget=new GLWidget;
    setCentralWidget(glwidget);
}

MainWindow::~MainWindow(){

}
