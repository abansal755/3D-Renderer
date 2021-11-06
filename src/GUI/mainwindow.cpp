#include "mainwindow.h"
#include "MainWindow/ListWidget/modelpropertieswidget.h"
#include "MainWindow/ListWidget/ListWidgetItem/colormodellistwidgetitem.h"
#include "settingswidget.h"
#include "src/OpenGL/Models/colormodel.h"
#include "src/OpenGL/Shaders/lightshader.h"
#include "src/GUI/MainWindow/ListWidget/ListWidgetItem/conemodellistwidgetitem.h"
#include "src/GUI/MainWindow/ListWidget/ListWidgetItem/cylindermodellistwidgetitem.h"
#include "src/GUI/MainWindow/ListWidget/ListWidgetItem/spheremodellistwidgetitem.h"
#include "qssloader.h"
#include "MainWindow/ListWidget/ModelPropertiesWidget/colormodelpropertieswidget.h"
#include "MainWindow/ListWidget/ModelPropertiesWidget/ColorModelPropertiesWidgets/conemodelpropertieswidget.h"
#include "MainWindow/ListWidget/ModelPropertiesWidget/ColorModelPropertiesWidgets/cylindermodelpropertieswidget.h"
#include "MainWindow/ListWidget/ModelPropertiesWidget/ColorModelPropertiesWidgets/spheremodelpropertieswidget.h"

#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QSplitter>
#include <QCloseEvent>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

MainWindow::MainWindow(QWidget*parent):QMainWindow(parent){
    resize(800,600);

    QVBoxLayout*vb1=new QVBoxLayout;
    settingsWidget=new SettingsWidget;
    listWidget=new ListWidget(vb1);
    aboutDialog=new AboutDialog(this);

    QWidget*central=new QWidget;
        QHBoxLayout*hb1=new QHBoxLayout;
            QSplitter*sp1=new QSplitter(Qt::Horizontal);
                glwidget=new GLWidget(listWidget,settingsWidget,this);
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
            QAction* addCylinderActiion=addPrimitivesMenu->addAction("Cylinder");
                connect(addCylinderActiion,SIGNAL(triggered()),this,SLOT(addCylinder()));
            QAction* addSphereAction=addPrimitivesMenu->addAction("Sphere");
                connect(addSphereAction,SIGNAL(triggered()),this,SLOT(addSphere()));
        QAction* saveAsAction=fileMenu->addAction("Save Scene As");
            connect(saveAsAction,SIGNAL(triggered()),this,SLOT(saveAs()));
        QAction* loadAction=fileMenu->addAction("Load Scene");
            connect(loadAction,SIGNAL(triggered()),this,SLOT(loadScene()));
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
        QApplication::exit(0);
        return;
    }
    int res=QMessageBox::question(this,"Question","Are you sure you want to exit? Make sure to save your work.",QMessageBox::Yes|QMessageBox::No);
    if(res==QMessageBox::Yes) QApplication::exit(0);
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
    item->setObjectType(ObjectType::Plane);
    Model* model=item->getModelPropertiesWidget()->getModel();
    model->setMesh(planeMesh);
    model->setShader(glwidget->getFlatShader());

    listWidget->addItem(item);
    change=true;
}

void MainWindow::addCube(){
    Mesh* cubeMesh=glwidget->getCubeMesh();
    ColorModelListWidgetItem* item=new ColorModelListWidgetItem("Cube"+QString::number(cubeCount++));
    item->setObjectType(ObjectType::Cube);
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

void MainWindow::addCylinder(){
    CylinderModelListWidgetItem* item=new CylinderModelListWidgetItem(glwidget,"Cylinder"+QString::number(cylinderCount++));
    Model* model=item->getModelPropertiesWidget()->getModel();
    model->setShader(glwidget->getFlatShader());

    listWidget->addItem(item);
    change=true;
}

void MainWindow::addSphere(){
    SphereModelListWidgetItem* item=new SphereModelListWidgetItem(glwidget,"Sphere"+QString::number(sphereCount++));
    Model* model=item->getModelPropertiesWidget()->getModel();
    model->setShader(glwidget->getPhongShader());

    listWidget->addItem(item);
    change=true;
}

void MainWindow::settings(){
    settingsWidget->show();
}

void MainWindow::about(){
    aboutDialog->open();
}

int MainWindow::newScene(){
    int response=QMessageBox::Yes;
    if(change)
        response=QMessageBox::warning(this,"Warning","Are you sure you want to create a new scene? Make sure to save your work.",QMessageBox::Yes|QMessageBox::No);
    if(response==QMessageBox::Yes){
        listWidget->clear();
        resetCounts();
    }
    return response;
}

void MainWindow::resetCounts(){
    planeCount=0;
    cubeCount=0;
    coneCount=0;
    cylinderCount=0;
    sphereCount=0;
    change=false;
}

void MainWindow::renderViewport(){
    QString path=QFileDialog::getSaveFileName(NULL,"Save Render",QString(),"*.bmp *.jpg *.jpeg *.png *.ppm *.xbm *.xpm");
    if(path.isEmpty()) return;
    QImage image=glwidget->renderViewport();
    bool res=image.save(path);
    if(!res) QMessageBox::critical(NULL,"Critical","Unable to save the render at the path specified");
}

void MainWindow::saveAs(){
    QJsonObject obj=glwidget->sceneToJson();
    QJsonDocument doc(obj);
    QString path=QFileDialog::getSaveFileName(NULL,"Save Scene As",QString(),"*.scene");
    if(path.isEmpty()) return;
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly)){
        qDebug()<<"Unable to write to "<<path;
        return;
    }
    file.write(doc.toJson());
    file.close();
}

void MainWindow::loadScene(QString path){
    if(path.isEmpty())
        path=QFileDialog::getOpenFileName(NULL,"Load Scene",QString(),"*.scene");
    if(path.isEmpty()) return;
    if(newScene()!=QMessageBox::Yes) return;

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Unable to read from "<<path;
        return;
    }
    QJsonDocument doc=QJsonDocument::fromJson(file.readAll());
    file.close();
    if(doc.isNull()){
        qDebug()<<"Unable to parse "<<path;
        return;
    }
    QJsonObject obj=doc.object();
    if(!obj["objects"].isArray()){
        qDebug()<<"objects not an array";
        return;
    }
    QJsonArray objs=obj["objects"].toArray();
    for(auto it=objs.begin();it!=objs.end();it++){
        if(!it->isObject()){
            qDebug()<<"Not and object";
            continue;
        }
        QJsonObject curr=it->toObject();
        QString type=curr["type"].toString();
        int idx=listWidget->count();
        if(type=="Plane") addPlane();
        else if(type=="Cube") addCube();
        else if(type=="Cone") addCone();
        else if(type=="Cylinder") addCylinder();
        else if(type=="Sphere") addSphere();
        else continue;
        ColorModelListWidgetItem*item=(ColorModelListWidgetItem*)listWidget->getCustomItem(idx);
        ColorModelPropertiesWidget*wg=(ColorModelPropertiesWidget*)item->getModelPropertiesWidget();
        QJsonObject trans=curr["translate"].toObject();
            wg->setTranslateX(trans["x"].toDouble());
            wg->setTranslateY(trans["y"].toDouble());
            wg->setTranslateZ(trans["z"].toDouble());
        QJsonObject rotate=curr["rotate"].toObject();
            wg->setRotateX(rotate["x"].toDouble());
            wg->setRotateZ(rotate["y"].toDouble());
            wg->setRotateY(rotate["z"].toDouble());
        QJsonObject scale=curr["scale"].toObject();
            wg->setScaleX(scale["x"].toDouble());
            wg->setScaleY(scale["y"].toDouble());
            wg->setScaleZ(scale["z"].toDouble());
            wg->setScaleUniform(scale["uniform"].toDouble());
        if(isColorJsonValid(curr["color"].toObject())) wg->setColor(jsonToQColor(curr["color"].toObject()));
        if(curr["name"].isString()) wg->setText(curr["name"].toString());
        if(type=="Cone"){
            auto*wg2=(ConeModelPropertiesWidget*)wg;
            wg2->setRadius(curr["radius"].toDouble());
            wg2->setHeight(curr["height"].toDouble());
            wg2->setNumLines(curr["numLines"].toInt());
        }
        else if(type=="Cylinder"){
            auto*wg2=(CylinderModelPropertiesWidget*)wg;
            wg2->setRadius(curr["radius"].toDouble());
            wg2->setHeight(curr["height"].toDouble());
            wg2->setNumLines(curr["numLines"].toInt());
        }
        else if(type=="Sphere"){
            auto*wg2=(SphereModelPropertiesWidget*)wg;
            wg2->setRadius(curr["radius"].toDouble());
            wg2->setNumLines(curr["numLines"].toInt());
        }
    }
}

bool MainWindow::isColorJsonValid(QJsonObject json){
    if(!json["red"].isDouble()) return false;
    if(!json["green"].isDouble()) return false;
    if(!json["blue"].isDouble()) return false;
    return true;
}

QColor MainWindow::jsonToQColor(QJsonObject json){
    QColor color;
    color.setRed(json["red"].toInt());
    color.setGreen(json["green"].toInt());
    color.setBlue(json["blue"].toInt());
    if(json["alpha"].isDouble()) color.setAlpha(json["alpha"].toInt());
    else color.setAlpha(255);
    return color;
}
