#include "mainwindow.h"
#include "MainWindow/ListWidget/modelpropertieswidget.h"
#include "MainWindow/ListWidget/ListWidgetItem/flatmodellistwidgetitem.h"
#include "settingswidget.h"
#include "src/OpenGL/Models/flatmodel.h"
#include "src/OpenGL/Shaders/flatshader.h"

#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
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
            QAction* addPlaneAction=addPrimitivesMenu->addAction("Plane");
                connect(addPlaneAction,SIGNAL(triggered()),this,SLOT(addPlane()));
            QAction* addCubeAction=addPrimitivesMenu->addAction("Cube");
                connect(addCubeAction,SIGNAL(triggered()),this,SLOT(addCube()));
        QAction* exitAction=fileMenu->addAction("Exit");
            connect(exitAction,SIGNAL(triggered()),this,SLOT(exitApp()));
    QMenu* windowMenu=menuBar()->addMenu("Window");
        QAction* settingsAction=windowMenu->addAction("Settings");
            connect(settingsAction,SIGNAL(triggered()),this,SLOT(settings()));
    QMenu* renderMenu=menuBar()->addMenu("Render");
        QAction* renderViewportAction=renderMenu->addAction("Render Viewport");
            connect(renderViewportAction,SIGNAL(triggered()),this,SLOT(renderViewport()));
}

MainWindow::~MainWindow(){
    delete settingsWidget;
}

void MainWindow::exitApp(){
    QApplication::exit(0);
}

void MainWindow::addPlane(){
    Mesh* planeMesh=glwidget->getPlaneMesh();
    FlatModelListWidgetItem* item=new FlatModelListWidgetItem("Plane"+QString::number(planeCount++));
    Model* model=item->getModelPropertiesWidget()->getModel();
    model->setMesh(planeMesh);
    model->setShader(glwidget->getFlatShader());

    listWidget->addItem(item);
}

void MainWindow::addCube(){
    Mesh* cubeMesh=glwidget->getCubeMesh();
    FlatModelListWidgetItem* item=new FlatModelListWidgetItem("Cube"+QString::number(cubeCount++));
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
    planeCount=0;
    cubeCount=0;
}

void MainWindow::renderViewport(){
    QString path=QFileDialog::getSaveFileName(NULL,"Save Render",QString(),"*.bmp *.jpg *.jpeg *.png *.ppm *.xbm *.xpm");
    if(path.isEmpty()) return;
    QImage image=glwidget->renderViewport();
    bool res=image.save(path);
    if(!res) QMessageBox::critical(NULL,"Critical","Unable to save the render at the path specified");
}
