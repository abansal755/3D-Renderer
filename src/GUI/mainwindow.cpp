#include "mainwindow.h"
#include "MainWindow/ListWidget/modelpropertieswidget.h"
#include "MainWindow/ListWidget/listwidgetitem.h"
#include "settingsdialog.h"

#include <QApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget*parent):QMainWindow(parent){
    resize(800,600);

    QMenu* fileMenu=menuBar()->addMenu("File");
    QMenu* addPrimitivesMenu=fileMenu->addMenu("Add Primitives");
    QAction* exitAction=fileMenu->addAction("Exit");
    connect(exitAction,SIGNAL(triggered()),this,SLOT(exitApp()));

    QAction* addCubeAction=addPrimitivesMenu->addAction("Cube");
    connect(addCubeAction,SIGNAL(triggered()),this,SLOT(addCube()));

    QMenu* viewMenu=menuBar()->addMenu("View");
    QAction* settingsAction=viewMenu->addAction("Settings");
    connect(settingsAction,SIGNAL(triggered()),this,SLOT(settings()));

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

    settingsDialog=new SettingsDialog(this);
}

void MainWindow::exitApp(){
    QApplication::exit(0);
}

void MainWindow::addCube(){
    Mesh* cubeMesh=glwidget->getCubeMesh();
    ListWidgetItem* item=new ListWidgetItem("Cube"+QString::number(cubeCount++));
    Model* model=item->getModelPropertiesWidget()->getModel();
    model->setMesh(cubeMesh);
    model->setShader(glwidget->getFlatShader());

    listWidget->addItem(item);
}

void MainWindow::settings(){
    settingsDialog->open();
}

void MainWindow::setBGColor(const QColor& color){
    glwidget->setBGColor(color);
}

void MainWindow::setLightColor(const QColor& color){
    glwidget->setLightColor(color);
}
