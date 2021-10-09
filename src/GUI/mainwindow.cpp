#include "mainwindow.h"
#include "MainWindow/ListWidget/ListWidgetItems/modellistwidgetitem.h"
#include "MainWindow/ListWidget/PropertiesWidgets/modelpropertieswidget.h"

#include <QSplitter>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QMenuBar>
#include <QApplication>
#include <QDoubleSpinBox>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent){
    resize(800,600);

    QMenu*fileMenu=menuBar()->addMenu("File");
        QAction*exitAction=fileMenu->addAction("Exit");
            connect(exitAction,SIGNAL(triggered()),this,SLOT(exitSlot()));
    QMenu*sceneMenu=menuBar()->addMenu("Scene");
        QMenu*addPrimitivesMenu=sceneMenu->addMenu("Add Primitives");
            QAction*addPlaneAction=addPrimitivesMenu->addAction("Plane");
                connect(addPlaneAction,SIGNAL(triggered()),this,SLOT(addPlane()));


    QVBoxLayout*vb1=new QVBoxLayout;

    QWidget*central=new QWidget;
        QHBoxLayout*hb1=new QHBoxLayout;
            QSplitter*sp1=new QSplitter(Qt::Horizontal);
                QSplitter*sp2=new QSplitter(Qt::Vertical);
                    QTabWidget*tabw1=new QTabWidget;
                        models=new ListWidget(vb1);
                        tabw1->addTab(models,"Models");
                        //lights
                    sp2->addWidget(tabw1);
                    QTabWidget*tabw2=new QTabWidget;
                        //materials
                        //textures
                    sp2->addWidget(tabw2);
                sp1->addWidget(sp2);
                glwidget=new GLWidget;
                sp1->addWidget(glwidget);
                QSplitter*sp3=new QSplitter(Qt::Vertical);
                    QTabWidget*tabw3=new QTabWidget;
                        QWidget*modelEditor=new QWidget;
                            modelEditor->setLayout(vb1);
                        tabw3->addTab(modelEditor,"Model Editor");
                        //lights
                    sp3->addWidget(tabw3);
                    QTabWidget*tabw4=new QTabWidget;
                        //materials
                        //textures
                    sp3->addWidget(tabw4);
                sp1->addWidget(sp3);
            hb1->addWidget(sp1);
        central->setLayout(hb1);
    setCentralWidget(central);
}


void MainWindow::exitSlot(){
    QApplication::exit(0);
}

void MainWindow::addPlane(){
    ModelListWidgetItem* item=new ModelListWidgetItem("Plane"+QString::number(planeCount++));
    models->addItem(item);
    ModelPropertiesWidget*widget=(ModelPropertiesWidget*)item->getPropertiesWidget();
    widget->getModel()->setMesh(glwidget->getPlaneMesh());
}
