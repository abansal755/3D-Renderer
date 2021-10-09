#include "settingswidget.h"
#include "mainwindow.h"
#include "qssloader.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QFile>

SettingsWidget::SettingsWidget(QWidget*parent):QWidget(parent){
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowFlag(Qt::CustomizeWindowHint);
    setWindowFlag(Qt::WindowMaximizeButtonHint,false);
    setWindowFlag(Qt::WindowMinimizeButtonHint,false);

    setWindowTitle("Settings");
    setObjectName("central");

    //setting default values
    defaultBGColor=QColor(0,0,0);
    defaultLightColor=QColor(255,255,255);

    bgColorDialog=new QColorDialog(defaultBGColor,this);
    bgColorDialog->setOptions(QColorDialog::NoButtons|QColorDialog::ShowAlphaChannel);

    lightColorDialog=new QColorDialog(defaultLightColor,this);
    lightColorDialog->setOptions(QColorDialog::NoButtons);

    defaultGridColor=QColor(255,255,255);
    gridColorDialog=new QColorDialog(defaultGridColor,this);
    gridColorDialog->setOptions(QColorDialog::NoButtons);

    QVBoxLayout*vb1=new QVBoxLayout;
        QGroupBox*box1=new QGroupBox("Viewport");
            QVBoxLayout*vb5=new QVBoxLayout;
                QHBoxLayout*hb1=new QHBoxLayout;
                    QLabel*label1=new QLabel("Background Color");
                    hb1->addWidget(label1);
                    QPushButton*btn1=new QPushButton("Change Background Color");
                        connect(btn1,SIGNAL(clicked()),this,SLOT(btn1Clicked()));
                    hb1->addWidget(btn1);
                vb5->addLayout(hb1);
                QHBoxLayout*hb5=new QHBoxLayout;
                    QLabel*label4=new QLabel("V-Sync");
                    hb5->addWidget(label4);
                    cb1=new QComboBox;
                        cb1->addItem("Off");
                        cb1->addItem("On");
                        cb1->addItem("Half");
                        cb1->setCurrentIndex(defaultVsync);
                        connect(cb1,SIGNAL(activated(int)),this,SLOT(cb1Changed()));
                    hb5->addWidget(cb1);
                vb5->addLayout(hb5);
            box1->setLayout(vb5);
        vb1->addWidget(box1);
        QGroupBox*box2=new QGroupBox("Light");
            QVBoxLayout*vb2=new QVBoxLayout;
                QHBoxLayout*hb2=new QHBoxLayout;
                    QLabel*label2=new QLabel("Light Color");
                    hb2->addWidget(label2);
                    QPushButton*btn2=new QPushButton("Change Light Color");
                        connect(btn2,SIGNAL(clicked()),this,SLOT(btn2Clicked()));
                    hb2->addWidget(btn2);
                vb2->addLayout(hb2);
                slider1=new SliderFloat("Ambient Light Intensity",NULL,0,100,100);
                    slider1->setValue(defaultAmbientLightIntensity);
                vb2->addWidget(slider1);
                slider2=new SliderFloat("Diffuse Light Intensity",NULL,0,100,100);
                        slider2->setValue(defaultDiffuseLightIntensity);
                vb2->addWidget(slider2);
            box2->setLayout(vb2);
        vb1->addWidget(box2);
        box3=new QGroupBox("Grid");
            box3->setCheckable(true);
            box3->setChecked(defaultIsShowGridChecked);
            QVBoxLayout*vb3=new QVBoxLayout;
                QHBoxLayout*hb3=new QHBoxLayout;
                    QLabel*label3=new QLabel("Grid Color");
                    hb3->addWidget(label3);
                    QPushButton*btn3=new QPushButton("Change Grid Color");
                        connect(btn3,SIGNAL(clicked()),this,SLOT(btn3Clicked()));
                    hb3->addWidget(btn3);
                vb3->addLayout(hb3);
                slider3=new SliderFloat("Grid Side Length",NULL,1,1000,100);
                    slider3->setValue(defaultGridSideLength);
                        connect(slider3,SIGNAL(valueChanged(double)),this,SLOT(gridChanged()));
                vb3->addWidget(slider3);
                slider4=new SliderInt("Grid Number Of Lines",NULL,2,50);
                    slider4->setValue(defaultGridNumLines);
                        connect(slider4,SIGNAL(valueChanged(int)),this,SLOT(gridChanged()));
                vb3->addWidget(slider4);
            box3->setLayout(vb3);
        vb1->addWidget(box3);
        QGroupBox*box4=new QGroupBox("Camera");
            QVBoxLayout*vb4=new QVBoxLayout;
                slider5=new SliderFloat("Camera Move Speed",NULL,1,2000,100);
                    slider5->setValue(defaultCameraMoveSpeed);
                vb4->addWidget(slider5);
                slider6=new SliderFloat("Camera Turn Speed",NULL,1,10000,100000);
                    slider6->setSpinBoxWidth(150);
                    slider6->setDecimals(4);
                    slider6->setValue(defaultCameraTurnSpeed);
                vb4->addWidget(slider6);
                slider7=new SliderFloat("Camera FOV",NULL,1,1000,320);
                    slider7->setValue(defaultCameraFOV);
                vb4->addWidget(slider7);
                slider8=new SliderFloat("Camera Near Z-Plane",NULL,1,10000,1000);
                    slider8->setDecimals(3);
                    slider8->setSpinBoxWidth(100);
                    slider8->setValue(defaultCameraZNear);
                vb4->addWidget(slider8);
                slider9=new SliderFloat("Camera Far Z-Plane",NULL,1,10000,10);
                    slider9->setDecimals(3);
                    slider9->setSpinBoxWidth(100);
                    slider9->setValue(defaultCameraZFar);
                vb4->addWidget(slider9);
            box4->setLayout(vb4);
        vb1->addWidget(box4);
        QHBoxLayout*hb4=new QHBoxLayout;
            hb4->addStretch();
            QPushButton*btn4=new QPushButton("Reset");
                connect(btn4,SIGNAL(clicked()),this,SLOT(btn4Clicked()));
            hb4->addWidget(btn4);
        vb1->addLayout(hb4);
    setLayout(vb1);

    qssLoader(this,":/qss/settingswidget.qss");

    loadSettings();
}

SettingsWidget::~SettingsWidget(){
    QJsonDocument doc(settingsToJson());
    QFile file("settings.json");
    if(!file.open(QIODevice::WriteOnly)){
        qDebug()<<"Unable to write settings.json";
        return;
    }
    file.write(doc.toJson());
    file.close();
}

void SettingsWidget::btn1Clicked(){
    bgColorDialog->open();
}

void SettingsWidget::btn2Clicked(){
    lightColorDialog->open();
}

void SettingsWidget::btn3Clicked(){
    gridColorDialog->open();
}

void SettingsWidget::btn4Clicked(){
    setBGColor(defaultBGColor);
    setVsyncMode(defaultVsync);
    setLightColor(defaultLightColor);
    setAmbientLightIntensity(defaultAmbientLightIntensity);
    setDiffuseLightIntensity(defaultDiffuseLightIntensity);
    setGridColor(defaultGridColor);
    setGridSideLength(defaultGridSideLength);
    setGridNumLines(defaultGridNumLines);
    setIsShowGridChecked(defaultIsShowGridChecked);
    setCameraMoveSpeed(defaultCameraMoveSpeed);
    setCameraTurnSpeed(defaultCameraTurnSpeed);
    setCameraFOV(defaultCameraFOV);
    setCameraZNear(defaultCameraZNear);
    setCameraZFar(defaultCameraZFar);

    cb1Changed();
}

void SettingsWidget::cb1Changed(){
    QMessageBox::information(this,"Information","Please restart the application in order to see V-Sync changes.");
}

void SettingsWidget::setVsyncMode(int value){
    cb1->setCurrentIndex(value);
    QSurfaceFormat format=QSurfaceFormat::defaultFormat();
    format.setSwapInterval(value);
    QSurfaceFormat::setDefaultFormat(format);
}

bool SettingsWidget::isChangeInGrid(){
    if(changeInGrid){
        changeInGrid=false;
        return true;
    }
    return false;
}

void SettingsWidget::gridChanged(){
    changeInGrid=true;
}

QJsonObject SettingsWidget::qColorToJson(QColor color,bool alpha){
    QJsonObject obj;
    obj["red"]=color.red();
    obj["green"]=color.green();
    obj["blue"]=color.blue();
    if(alpha) obj["alpha"]=color.alpha();
    return obj;
}

bool SettingsWidget::isColorJsonValid(QJsonObject json){
    if(!json["red"].isDouble()) return false;
    if(!json["green"].isDouble()) return false;
    if(!json["blue"].isDouble()) return false;
    return true;
}

QColor SettingsWidget::jsonToQColor(QJsonObject json){
    QColor color;
    color.setRed(json["red"].toInt());
    color.setGreen(json["green"].toInt());
    color.setBlue(json["blue"].toInt());
    if(json["alpha"].isDouble()) color.setAlpha(json["alpha"].toInt());
    else color.setAlpha(255);
    return color;
}

QJsonObject SettingsWidget::settingsToJson(){
    QJsonObject obj;
        QJsonObject viewportObj;
            viewportObj["backgroundColor"]=qColorToJson(getBGColor(),false);
            viewportObj["vsync"]=getVsyncMode();
        obj["viewport"]=viewportObj;
        QJsonObject lightObj;
            lightObj["lightColor"]=qColorToJson(getLightColor(),false);
            lightObj["ambientLightIntensity"]=getAmbientLightIntensity();
            lightObj["diffuseLightIntensity"]=getDiffuseLightIntensity();
        obj["light"]=lightObj;
        QJsonObject gridObj;
            gridObj["showGrid"]=isShowGridChecked();
            gridObj["gridColor"]=qColorToJson(getGridColor());
            gridObj["gridSideLength"]=getGridSideLength();
            gridObj["gridNumLines"]=getGridNumLines();
        obj["grid"]=gridObj;
        QJsonObject cameraObj;
            cameraObj["cameraMoveSpeed"]=getCameraMoveSpeed();
            cameraObj["cameraTurnSpeed"]=getCameraTurnSpeed();
            cameraObj["cameraFOV"]=getCameraFOV();
            cameraObj["cameraZNear"]=getCameraZNear();
            cameraObj["cameraZFar"]=getCameraZFar();
        obj["camera"]=cameraObj;
    return obj;
}

void SettingsWidget::loadSettings(){
    QFile file("settings.json");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Unable to read from settings.json";
        return;
    }
    QJsonDocument doc=QJsonDocument::fromJson(file.readAll());
    file.close();
    if(doc.isNull()){
        qDebug()<<"Unable to parse from settings.json";
        return;
    }
    QJsonObject obj=doc.object();
        QJsonObject viewportObj=obj["viewport"].toObject();
            if(isColorJsonValid(viewportObj["backgroundColor"].toObject())) setBGColor(jsonToQColor(viewportObj["backgroundColor"].toObject()));
            if(viewportObj["vsync"].isDouble()) setVsyncMode(viewportObj["vsync"].toInt());
        QJsonObject lightObj=obj["light"].toObject();
            if(isColorJsonValid(lightObj["lightColor"].toObject())) setLightColor(jsonToQColor(lightObj["lightColor"].toObject()));
            if(lightObj["ambientLightIntensity"].isDouble()) setAmbientLightIntensity(lightObj["ambientLightIntensity"].toDouble());
            if(lightObj["diffuseLightIntensity"].isDouble()) setDiffuseLightIntensity(lightObj["diffuseLightIntensity"].toDouble());
        QJsonObject gridObj=obj["grid"].toObject();
            if(gridObj["showGrid"].isBool()) setIsShowGridChecked(gridObj["showGrid"].toBool());
            if(isColorJsonValid(gridObj["gridColor"].toObject())) setGridColor(jsonToQColor(gridObj["gridColor"].toObject()));
            if(gridObj["gridSideLength"].isDouble()) setGridSideLength(gridObj["gridSideLength"].toDouble());
            if(gridObj["gridNumLines"].isDouble()) setGridNumLines(gridObj["gridNumLines"].toInt());
        QJsonObject cameraObj=obj["camera"].toObject();
            if(cameraObj["cameraMoveSpeed"].isDouble()) setCameraMoveSpeed(cameraObj["cameraMoveSpeed"].toDouble());
            if(cameraObj["cameraTurnSpeed"].isDouble()) setCameraTurnSpeed(cameraObj["cameraTurnSpeed"].toDouble());
            if(cameraObj["cameraFOV"].isDouble()) setCameraFOV(cameraObj["cameraFOV"].toDouble());
            if(cameraObj["cameraZNear"].isDouble()) setCameraZNear(cameraObj["cameraZNear"].toDouble());
            if(cameraObj["cameraZFar"].isDouble()) setCameraZFar(cameraObj["cameraZFar"].toDouble());
}
