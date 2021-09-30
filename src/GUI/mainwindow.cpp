#include "mainwindow.h"
#include "MainWindow/ListWidget/modelpropertieswidget.h"
#include "MainWindow/ListWidget/listwidgetitem.h"
#include "settingswidget.h"

#include <QApplication>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget*parent):QMainWindow(parent){
    resize(800,600);

    settingsWidget=new SettingsWidget;

    QWidget*central=new QWidget;
        QHBoxLayout*hb1=new QHBoxLayout;
            QVBoxLayout*vb1=new QVBoxLayout;
            listWidget=new ListWidget(vb1);
            glwidget=new GLWidget(listWidget,settingsWidget);
            hb1->addWidget(glwidget,1);
            hb1->addLayout(vb1);
                vb1->addWidget(listWidget);
        central->setLayout(hb1);
    setCentralWidget(central);

    QMenu* fileMenu=menuBar()->addMenu("File");
        QAction* newSceneAction=fileMenu->addAction("New Scene");
            connect(newSceneAction,SIGNAL(triggered()),this,SLOT(newScene()));
        QMenu* addPrimitivesMenu=fileMenu->addMenu("Add Primitives");
            QAction* addCubeAction=addPrimitivesMenu->addAction("Cube");
                connect(addCubeAction,SIGNAL(triggered()),this,SLOT(addCube()));
        QAction* exitAction=fileMenu->addAction("Exit");
            connect(exitAction,SIGNAL(triggered()),this,SLOT(exitApp()));
    QMenu* windowMenu=menuBar()->addMenu("Window");
        QAction* settingsAction=windowMenu->addAction("Settings");
            connect(settingsAction,SIGNAL(triggered()),this,SLOT(settings()));
}

MainWindow::~MainWindow(){
    delete settingsWidget;
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
    settingsWidget->show();
}

void MainWindow::newScene(){
    int response=QMessageBox::warning(this,"Warning","Are you sure you want to create a new scene?",QMessageBox::Yes|QMessageBox::No);
    if(response!=QMessageBox::Yes) return;
    listWidget->clear();
    resetCounts();
}

void MainWindow::resetCounts(){
    cubeCount=0;
}
