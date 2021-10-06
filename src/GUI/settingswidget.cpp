#include "settingswidget.h"
#include "mainwindow.h"
#include "src/OpenGL/camera.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

SettingsWidget::SettingsWidget(QWidget*parent):QWidget(parent){
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowTitle("Settings");

    QColor defaultBGColor(0,0,0);
    bgColorDialog=new QColorDialog(defaultBGColor,this);
    bgColorDialog->setOptions(QColorDialog::NoButtons|QColorDialog::ShowAlphaChannel);

    QColor defaultLightColor(255,255,255);
    lightColorDialog=new QColorDialog(defaultLightColor,this);
    lightColorDialog->setOptions(QColorDialog::NoButtons);

    QColor defaultGridColor(255,255,255);
    gridColorDialog=new QColorDialog(defaultGridColor,this);
    gridColorDialog->setOptions(QColorDialog::NoButtons);

    QVBoxLayout*vb1=new QVBoxLayout;
        QGroupBox*box1=new QGroupBox("Background");
            QHBoxLayout*hb1=new QHBoxLayout;
                QLabel*label1=new QLabel("Background Color");
                hb1->addWidget(label1);
                QPushButton*btn1=new QPushButton("Change Background Color");
                    connect(btn1,SIGNAL(clicked()),this,SLOT(btn1Clicked()));
                hb1->addWidget(btn1);
             box1->setLayout(hb1);
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
                    float defaultAmbientLightIntensity=0.25;
                    slider1->setValue(defaultAmbientLightIntensity);
                vb2->addWidget(slider1);
                slider2=new SliderFloat("Diffuse Light Intensity",NULL,0,100,100);
                        float defaultDiffuseLightIntensity=1;
                        slider2->setValue(defaultDiffuseLightIntensity);
                vb2->addWidget(slider2);
            box2->setLayout(vb2);
        vb1->addWidget(box2);
        box3=new QGroupBox("Grid");
            box3->setCheckable(true);
            box3->setChecked(true);
            QVBoxLayout*vb3=new QVBoxLayout;
                QHBoxLayout*hb3=new QHBoxLayout;
                    QLabel*label3=new QLabel("Grid Color");
                    hb3->addWidget(label3);
                    QPushButton*btn3=new QPushButton("Change Grid Color");
                        connect(btn3,SIGNAL(clicked()),this,SLOT(btn3Clicked()));
                    hb3->addWidget(btn3);
                vb3->addLayout(hb3);
                slider3=new SliderFloat("Grid Side Length",NULL,1,1000,100);
                    float defaultGridSideLength=5;
                    slider3->setValue(defaultGridSideLength);
                        connect(slider3,SIGNAL(valueChanged(double)),this,SLOT(gridChanged()));
                vb3->addWidget(slider3);
                slider4=new SliderInt("Grid Number Of Lines",NULL,2,50);
                    int defaultGridNumLines=10;
                    slider4->setValue(defaultGridNumLines);
                        connect(slider4,SIGNAL(valueChanged(int)),this,SLOT(gridChanged()));
                vb3->addWidget(slider4);
            box3->setLayout(vb3);
        vb1->addWidget(box3);
        QGroupBox*box4=new QGroupBox("Camera");
            QVBoxLayout*vb4=new QVBoxLayout;
                slider5=new SliderFloat("Camera Move Speed",NULL,1,2000,100);
                    float defaultCameraMoveSpeed=10;
                    slider5->setValue(defaultCameraMoveSpeed);
                vb4->addWidget(slider5);
                slider6=new SliderFloat("Camera Turn Speed",NULL,1,10000,100000);
                    float defaultCameraTurnSpeed=0.005;
                    slider6->setSpinBoxWidth(150);
                    slider6->setDecimals(4);
                    slider6->setValue(defaultCameraTurnSpeed);
                vb4->addWidget(slider6);
                slider7=new SliderFloat("Camera FOV",NULL,1,1000,320);
                    float defaultCameraFOV=PI/4;
                    slider7->setValue(defaultCameraFOV);
                vb4->addWidget(slider7);
                slider8=new SliderFloat("Camera Near Z-Plane",NULL,1,10000,1000);
                    float defaultCameraZNear=0.01;
                    slider8->setDecimals(3);
                    slider8->setSpinBoxWidth(100);
                    slider8->setValue(defaultCameraZNear);
                vb4->addWidget(slider8);
                slider9=new SliderFloat("Camera Far Z-Plane",NULL,1,10000,10);
                    float defaultCameraZFar=100;
                    slider9->setDecimals(3);
                    slider9->setSpinBoxWidth(100);
                    slider9->setValue(defaultCameraZFar);
                vb1->addWidget(slider9);
            box4->setLayout(vb4);
        vb1->addWidget(box4);
    setLayout(vb1);
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
