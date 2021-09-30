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

    QVBoxLayout*vb1=new QVBoxLayout;
        QHBoxLayout*hb1=new QHBoxLayout;
            QLabel*label1=new QLabel("Background Color");
            hb1->addWidget(label1);
            QPushButton*btn1=new QPushButton("Change Background Color");
                connect(btn1,SIGNAL(clicked()),this,SLOT(btn1Clicked()));
            hb1->addWidget(btn1);
        vb1->addLayout(hb1);
        QHBoxLayout*hb2=new QHBoxLayout;
            QLabel*label2=new QLabel("Light Color");
            hb2->addWidget(label2);
            QPushButton*btn2=new QPushButton("Change Light Color");
                connect(btn2,SIGNAL(clicked()),this,SLOT(btn2Clicked()));
            hb2->addWidget(btn2);
        vb1->addLayout(hb2);
        slider1=new SliderFloat("Ambient Light Intensity",NULL,0,100,100);
            float defaultAmbientLightIntensity=0.25;
            slider1->setValue(defaultAmbientLightIntensity);
        vb1->addWidget(slider1);
        slider2=new SliderFloat("Diffuse Light Intensity",NULL,0,100,100);
            float defaultDiffuseLightIntensity=1;
            slider2->setValue(defaultDiffuseLightIntensity);
        vb1->addWidget(slider2);
    setLayout(vb1);
}

void SettingsWidget::btn1Clicked(){
    bgColorDialog->open();
}

void SettingsWidget::btn2Clicked(){
    lightColorDialog->open();
}
