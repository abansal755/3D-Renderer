#include "mainwindow.h"
#include "MainWindow/ListWidget/modelpropertieswidget.h"
#include "MainWindow/ListWidget/ListWidgetItem/colormodellistwidgetitem.h"
#include "settingswidget.h"
#include "src/OpenGL/Models/colormodel.h"
#include "src/OpenGL/Shaders/lightshader.h"
#include "src/GUI/MainWindow/ListWidget/ListWidgetItem/conemodellistwidgetitem.h"
#include "qssloader.h"

#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QSplitter>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget*parent):QMainWindow(parent){
    resize(800,600);

    QVBoxLayout*vb1=new QVBoxLayout;
    settingsWidget=new SettingsWidget;
    listWidget=new ListWidget(vb1);
    aboutDialog=new AboutDialog(this);

    QWidget*central=new QWidget;
        QHBoxLayout*hb1=new QHBoxLayout;
            QSplitter*sp1=new QSplitter(Qt::Horizontal);
                glwidget=new GLWidget(listWidget,settingsWidget);
                sp1->addWidget(glwidget);
                QWidget*sidePanel=new QWidget;
                        sidePanel->setObjectName("side-panel");
                        vb1->setContentsMargins(0,0,0,0);
                        vb1->addWidget(listWidget);
                    sidePanel->setLayout(vb1);
                sp1->addWidget(sidePanel);
                sp1->setStretchFactor(0,1);
            hb1->addWidget(sp1);
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
            QAction* addConeAction=addPrimitivesMenu->addAction("Cone");
                connect(addConeAction,SIGNAL(triggered()),this,SLOT(addCone()));
        QAction* exitAction=fileMenu->addAction("Exit");
            connect(exitAction,SIGNAL(triggered()),this,SLOT(exitApp()));
    QMenu* windowMenu=menuBar()->addMenu("Window");
        QAction* settingsAction=windowMenu->addAction("Settings");
            connect(settingsAction,SIGNAL(triggered()),this,SLOT(settings()));
        QAction* aboutAction=windowMenu->addAction("About");
            connect(aboutAction,SIGNAL(triggered()),this,SLOT(about()));
    QMenu* renderMenu=menuBar()->addMenu("Render");
        QAction* renderViewportAction=renderMenu->addAction("Render Viewport");
            connect(renderViewportAction,SIGNAL(triggered()),this,SLOT(renderViewport()));

    qssLoader(this,":/qss/mainwindow.qss");
}

MainWindow::~MainWindow(){
    delete settingsWidget;
    delete aboutDialog;
}

void MainWindow::closeEvent(QCloseEvent *event){
    if(!change){
        event->accept();
        return;
    }
    int res=QMessageBox::question(this,"Question","Are you sure you want to exit? Make sure to save your work.",QMessageBox::Yes|QMessageBox::No);
    if(res==QMessageBox::Yes) event->accept();
    else event->ignore();
}

void MainWindow::exitApp(){
    if(!change){
        QApplication::exit(0);
        return;
    }
    int res=QMessageBox::question(this,"Question","Are you sure you want to exit? Make sure to save your work.",QMessageBox::Yes|QMessageBox::No);
    if(res==QMessageBox::Yes) QApplication::exit(0);
}

void MainWindow::addPlane(){
    Mesh* planeMesh=glwidget->getPlaneMesh();
    ColorModelListWidgetItem* item=new ColorModelListWidgetItem("Plane"+QString::number(planeCount++));
    Model* model=item->getModelPropertiesWidget()->getModel();
    model->setMesh(planeMesh);
    model->setShader(glwidget->getFlatShader());

    listWidget->addItem(item);
    change=true;
}

void MainWindow::addCube(){
    Mesh* cubeMesh=glwidget->getCubeMesh();
    ColorModelListWidgetItem* item=new ColorModelListWidgetItem("Cube"+QString::number(cubeCount++));
    Model* model=item->getModelPropertiesWidget()->getModel();
    model->setMesh(cubeMesh);
    model->setShader(glwidget->getFlatShader());

    listWidget->addItem(item);
    change=true;
}

void MainWindow::addCone(){
    ConeModelListWidgetItem* item=new ConeModelListWidgetItem(glwidget,"Cone"+QString::number(coneCount++));
    Model* model=item->getModelPropertiesWidget()->getModel();
    model->setShader(glwidget->getFlatShader());

    listWidget->addItem(item);
    change=true;
}

void MainWindow::settings(){
    settingsWidget->show();
}

void MainWindow::about(){
    aboutDialog->open();
}

void MainWindow::newScene(){
    int response=QMessageBox::warning(this,"Warning","Are you sure you want to create a new scene? Make sure to save your work.",QMessageBox::Yes|QMessageBox::No);
    if(response!=QMessageBox::Yes) return;
    listWidget->clear();
    resetCounts();
}

void MainWindow::resetCounts(){
    planeCount=0;
    cubeCount=0;
    coneCount=0;
    change=false;
}

void MainWindow::renderViewport(){
    QString path=QFileDialog::getSaveFileName(NULL,"Save Render",QString(),"*.bmp *.jpg *.jpeg *.png *.ppm *.xbm *.xpm");
    if(path.isEmpty()) return;
    QImage image=glwidget->renderViewport();
    bool res=image.save(path);
    if(!res) QMessageBox::critical(NULL,"Critical","Unable to save the render at the path specified");
}
