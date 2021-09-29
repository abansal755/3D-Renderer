#include "settingswidget.h"
#include "mainwindow.h"

SettingsWidget::SettingsWidget(QWidget*parent):QWidget(parent){
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowTitle("Settings");

    QColor defaultBGColor(0,0,0);
    bgColorDialog=new QColorDialog(defaultBGColor,this);
    bgColorDialog->setOptions(QColorDialog::NoButtons|QColorDialog::ShowAlphaChannel);

    QColor defaultLightColor(255,255,255);
    lightColorDialog=new QColorDialog(defaultLightColor,this);
    lightColorDialog->setOptions(QColorDialog::NoButtons);

    for(int i=0;i<4;i++) hb[i]=new QHBoxLayout;
    vb1=new QVBoxLayout;

    label[0]=new QLabel("Background Color");
    btn[0]=new QPushButton("Change Background Color");
    connect(btn[0],SIGNAL(clicked()),this,SLOT(btn0Clicked()));
    hb[0]->addWidget(label[0]);
    hb[0]->addWidget(btn[0]);

    label[1]=new QLabel("Light Color");
    btn[1]=new QPushButton("Change Light Color");
    connect(btn[1],SIGNAL(clicked()),this,SLOT(btn1Clicked()));
    hb[1]->addWidget(label[1]);
    hb[1]->addWidget(btn[1]);

    slider[0]=new SliderFloat("Ambient Light Intensity",NULL,0,100,100);
    hb[2]->addWidget(slider[0]);
    float defaultAmbientLightIntensity=0.25;
    slider[0]->setValue(defaultAmbientLightIntensity);

    slider[1]=new SliderFloat("Diffuse Light Intensity",NULL,0,100,100);
    hb[3]->addWidget(slider[1]);
    float defaultDiffuseLightIntensity=1;
    slider[1]->setValue(defaultDiffuseLightIntensity);

    for(int i=0;i<4;i++) vb1->addLayout(hb[i]);

    setLayout(vb1);
}

void SettingsWidget::btn0Clicked(){
    bgColorDialog->open();
}

void SettingsWidget::btn1Clicked(){
    lightColorDialog->open();
}
