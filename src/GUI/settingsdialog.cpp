#include "settingsdialog.h"
#include "mainwindow.h"

SettingsDialog::SettingsDialog(MainWindow*parent):QDialog((QWidget*)parent){
    setWindowFlag(Qt::WindowContextHelpButtonHint,false);

    QColor defaultBGColor(0,0,0);
    bgColorDialog=new QColorDialog(defaultBGColor,this);
    parent->setBGColor(defaultBGColor);

    btn1=new QPushButton("Change Color");
    connect(btn1,SIGNAL(clicked()),this,SLOT(btn1Clicked()));
    connect(bgColorDialog,SIGNAL(colorSelected(const QColor&)),parent,SLOT(setBGColor(const QColor&)));

    hb[0]=new QHBoxLayout;
    vb1=new QVBoxLayout;
    label[0]=new QLabel("Background Color");
    hb[0]->addWidget(label[0]);
    hb[0]->addWidget(btn1);
    vb1->addLayout(hb[0]);

    setLayout(vb1);
}

void SettingsDialog::btn1Clicked(){
    bgColorDialog->open();
}
